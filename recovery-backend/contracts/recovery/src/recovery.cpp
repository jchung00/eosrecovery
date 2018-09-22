#include "recovery.hpp"

namespace recovery{
    recovery_contract::recovery_contract(action_name self) : contract(self), m_recovery_env(self, self) {
        if (m_recovery_env.exists() == false) {
            m_recovery_env.set( wps_env(), _self );
        }
    }

    //@abi action
    void addrecovery(account_name owner, const vector<account_name>& backups){
        require_auth(owner);

        recovery_table recovery_accounts(_self, _self);

        auto itr = recovery_accounts.find(owner);
        eosio_assert(itr==recovery_accounts.end(), "Account already has recovery set up.");

        for(int i=0; i<backups.size(); i++){
            eosio_assert(is_account(backups.at(i)));
        }

        recovery_accounts.emplace(owner, [&](auto& recovery_info){
           recovery_info.owner = owner;
           recovery_info.backups = backups;
        });
    }

    //@abi action
    void rmvrecovery(){

    }

    //@abi action
    void recover(){

    }
}

EOSIO_ABI( recovery::recovery_contract, (addrecovery)(rmvrecovery)(recover))