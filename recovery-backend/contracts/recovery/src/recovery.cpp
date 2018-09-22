#include "recovery.hpp"

namespace recovery{
    recovery_contract::recovery_contract(action_name self) : contract(self) {}

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