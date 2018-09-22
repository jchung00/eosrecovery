#include "recovery.hpp"

namespace recovery{
    recovery_contract::recovery_contract(action_name self) : contract(self), m_recovery_env(self, self) {
        if (m_recovery_env.exists() == false) {
            m_recovery_env.set( wps_env(), _self );
        }
    }

    //@abi action
    void addrecovery(account_name owner, const vector<account_name>& backups, const string& cell_hash){
        require_auth(owner);
        eosio_assert(backups.size()>=2, "There should be at least 2 recovery accounts set up.");

        recovery_table recovery_accounts(_self, _self);

        auto itr = recovery_accounts.find(owner);
        eosio_assert(itr==recovery_accounts.end(), "Account already has recovery set up.");

        for(int i=0; i<backups.size(); i++){
            eosio_assert(is_account(backups.at(i)));
        }

        recovery_accounts.emplace(owner, [&](auto& recovery_info){
           recovery_info.owner = owner;
           recovery_info.backups = backups;
           recovery_info.cell_hash = cell_hash;
           recovery_info.rmv_recovery_start_time = 0;
           recovery_info.recover_start_time = 0;
        });
    }

    //@abi action
    void rmvrecovery(account_name owner){
        require_auth(owner);
    }

    //@abi action
    void recover(account_name owner, account_name requester, const public_key& new_key){
        require_auth(requester);
        eosio_assert(is_account(owner));
        eosio_assert( producer_key != eosio::public_key(), "Public key should not be the default value" );

        recovery_table recovery_accounts(_self, _self);
        auto itr = recovery_accounts.find(owner);
        eosio_assert(itr!=recovery_accounts.end(), "Account does not have recovery set up.");

        auto itr_backup = std::find((*itr).backups.begin(), (*itr).backups.end(), requester);
        eosio_assert(itr_backup != (*itr).backups.end(), "Account is not registered as one of the fallbacks.");

        in_recovery_table in_recovery(_self, _self);
        auto itr_account = in_recovery.find(owner);
        eosio_assert(itr_account == in_recovery.end(), "Account is already in the recovery process.");

        auto current_time = now();

        in_recovery.emplace(requester, [&]auto& in_recovery_info){
            in_recovery_info.owner = owner;
            in_recovery_info.backups = (*itr).backups;
            in_recovery_info.cell_hash = (*itr).cell_hash;
            in_recovery_info.recover_start_time = current_time;
            in_recovery_info.signed_recovery = vector<account_name> signed_recovery{requester};
            in_recovery_info.declined_recovery = vector<account_name> declined_recovery;
        });
    }

    //@abi action
    void reviewrec(account_name owner, account_name recoverer, bool agree){
        require_auth(recoverer);
        eosio_assert(is_accounts(owner));

        in_recovery_table in_recovery(_self, _self);
        auto itr = in_recovery.find(owner);
        eosio_assert(itr != in_recovery.end(), "Account is not in the recovery process");

        auto itr_backup = std::find((*itr).backups.begin(), (*itr).backups.end(), recoverer);
        eosio_assert(itr_backup != (*itr).backups.end(), "Account is not registered as one of the fallbacks.");

        auto current_time = now();

        uint64_t time_since_recover_start = current_time - (*itr).recover_start_time;

        if(time_since_recover_start >= seconds_per_day){
            in_recovery.erase(itr);
        }
        else{
            if(agree) {
                in_recovery.modify(itr, 0, [&](auto &in_recovery_info) {
                    in_recovery_info.signed_recovery = (*itr).signed_recovery.push_back(recoverer);
                });
                if((*itr).signed_recovery.size() >= (((*itr).backups.size() * 2) / 3) + 1){
                    /*
                     TO-DO UPDATE AUTH
                     */
                    in_recovery.erase(itr);
                }
            }
            else{
                in_recovery.modify(itr, 0, [&](auto &in_recovery_info) {
                    in_recovery_info.signed_recovery = (*itr).declined_recovery.push_back(recoverer);
                });
                if((*itr).declined_recovery.size() >= (((*itr).backups.size() * 2) / 3) + 1){
                    in_recovery.erase(itr);
                }
            }
        }
    }

}

EOSIO_ABI( recovery::recovery_contract, (addrecovery)(rmvrecovery)(recover))