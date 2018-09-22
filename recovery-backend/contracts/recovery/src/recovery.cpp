#include "recovery.hpp"

namespace recovery{
    recovery_contract::recovery_contract(action_name self) : contract(self), m_recovery_env(self, self) {
        if (m_recovery_env.exists() == false) {
            m_recovery_env.set( wps_env(), _self );
        }
    }

    //@abi action
    void addrecovery(){

    }

    //@abi action
    void rmvrecovery(){

    }

    //@abi action
    void recover(){

    }
}

EOSIO_ABI( recovery::recovery_contract, (addrecovery)(rmvrecovery)(recover))