#include "recovery.hpp"

namespace recovery{
    recovery_contract::recovery_contract(action_name self) : contract(self), m_recovery_env(self, self) {
        if (m_recovery_env.exists() == false) {
            m_recovery_env.set( recovery_env(), _self );
        }
    }

    //@abi action
    void recovery_contract::setenv(uint32_t set_recovery_delay_time){
        require_auth(_self);

        eosio_assert(set_recovery_delay_time >= 1 && set_recovery_delay_time <= 30, "Invalid delay time.");

        auto recovery_env = m_recovery_env.get();

        recovery_env.set_recovery_delay_time = set_recovery_delay_time;

        m_recovery_env.set( recovery_env, _self );
    }

    //@abi action
    void recovery_contract::setrecovery(account_name owner, const vector<account_name>& backups, const string& cell_hash){
        require_auth(owner);

        eosio_assert(backups.size()>=2, "There should be at least 2 recovery accounts set up.");
        eosio_assert(cell_hash.size()<1024, "Cell hash is too large");

        recovery_table recovery_accounts(_self, _self);
        auto itr = recovery_accounts.find(owner);

        for(int i=0; i<backups.size(); i++){
            eosio_assert(is_account(backups.at(i)), "Invalid recovery account.");
        }

        auto recovery_env = m_recovery_env.get();

        auto current_time = now();

        if(itr==recovery_accounts.end()){
            recovery_accounts.emplace(owner, [&](auto& recovery_info){
                recovery_info.owner = owner;
                recovery_info.backups = backups;
                //recovery_info.cell_hash = cell_hash;
                recovery_info.last_set_time = current_time;
                //recovery_info.rmv_recovery_start_time = 0;
                //recovery_info.recover_start_time = 0;
            });
        }

        else{
            recovery_accounts.modify(itr, 0, [&](auto& recovery_info){
                recovery_info.last_set_time = current_time;
            });

            transaction out{};

            out.actions.emplace_back(permission_level {_self, N(active)}, N(recoverykeys), N(chgrecovery),
            std::make_tuple(owner, backups));
            out.delay_sec = recovery_env.set_recovery_delay_time;
            out.send(owner, owner, true);
        }
    }

    //@abi action
    void recovery_contract::chgrecovery(account_name owner, const vector<account_name>& backups){
        require_auth(owner);

        recovery_table recovery_accounts(_self, _self);
        auto itr = recovery_accounts.find(owner);
        eosio_assert(itr != recovery_accounts.end(), "Account does not have recovery set up.");

        auto current_time = now();

        auto recovery_env = m_recovery_env.get();

        eosio_assert(current_time - (*itr).last_set_time > recovery_env.set_recovery_delay_time,
                     "Change recovery time has not been exceeded.");

        recovery_accounts.modify(itr, 0, [&](auto& recovery_info){
           recovery_info.backups = backups;
        });
    }

    //@abi action
    void recovery_contract::recover(account_name owner, account_name recoverer, const public_key& new_key, bool agree){
        require_auth(recoverer);
        eosio_assert(is_account(owner), "Non-existent account.");
        eosio_assert( new_key != eosio::public_key(), "Public key should not be the default value" );

        recovery_table recovery_accounts(_self, _self);
        auto itr = recovery_accounts.find(owner);
        eosio_assert(itr!=recovery_accounts.end(), "Account does not have recovery set up.");

        auto itr_backup = std::find((*itr).backups.begin(), (*itr).backups.end(), recoverer);
        eosio_assert(itr_backup != (*itr).backups.end(), "Account is not registered as one of the fallbacks.");

        in_recovery_table in_recovery(_self, _self);
        auto itr_account = in_recovery.find(owner);

        auto current_time = now();

        if(itr_account == in_recovery.end()){
            if(agree){
                in_recovery.emplace(recoverer, [&](auto& in_recovery_info){
                    in_recovery_info.owner = owner;
                    in_recovery_info.backups = (*itr).backups;
                    in_recovery_info.new_key = new_key;
                    //in_recovery_info.cell_hash = (*itr).cell_hash;
                    in_recovery_info.recover_start_time = current_time;
                    in_recovery_info.signed_recovery.push_back(recoverer);
                });
            }
            else{
                in_recovery.emplace(recoverer, [&](auto& in_recovery_info){
                    in_recovery_info.owner = owner;
                    in_recovery_info.backups = (*itr).backups;
                    in_recovery_info.new_key = new_key;
                    //in_recovery_info.cell_hash = (*itr).cell_hash;
                    in_recovery_info.recover_start_time = current_time;
                    in_recovery_info.declined_recovery.push_back(recoverer);
                });
            }
        }

        else{
            uint64_t time_since_recover_start = current_time - (*itr).recover_start_time;

            eosio_assert(new_key == (*itr_account).new_key, "Proposed public key is not the same.");

            if(time_since_recover_start >= seconds_per_day){
                in_recovery.erase(itr);
            }
            else{
                if(agree) {
                    in_recovery.modify(itr, 0, [&](auto& in_recovery_info) {
                        in_recovery_info.signed_recovery = (*itr).signed_recovery.push_back(recoverer);
                    });
                    if((*itr).signed_recovery.size() >= (((*itr).backups.size() * 2) / 3) + 1){
                        authority auth{ 1, {newKey, 1}, {} };
                        eosio::action(eosio::permission_level{_self, N(active)}, N(eosio), N(updateauth),
                        std::make_tuple( owner, active, owner, auth)).send();
                        in_recovery.erase(itr);
                    }
                }
                else{
                    in_recovery.modify(itr, 0, [&](auto& in_recovery_info) {
                        in_recovery_info.signed_recovery = (*itr).declined_recovery.push_back(recoverer);
                    });
                    if((*itr).declined_recovery.size() >= (((*itr).backups.size() * 2) / 3) + 1){
                        in_recovery.erase(itr);
                    }
                }
            }
        }
    }
} //recovery

EOSIO_ABI( recovery::recovery_contract, (setenv)(setrecovery)(chgrecovery)(recover))