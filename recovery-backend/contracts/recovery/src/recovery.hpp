#pragma once

#include <eosiolib/types.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/asset.hpp>

#include <string>
#include <vector>

namespace recovery {
    using std::string;
    using std::vector;

    using eosio::asset;

    class recovery_contract : public eosio::contract{
        public:
            explicit recovery_contract(action_name self);

            //@abi action
            void addrecovery(){

            }

            //@abi action
            void rmvrecovery(){

            }

            //@abi action
            void recover(){

            }

    };
}//recovery