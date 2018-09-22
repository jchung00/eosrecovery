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
    using std::set;

    using eosio::asset;

    //@abi table
    struct recovery_info{
        vector<account_name> backups;
    };

    //@abi table
    struct recovery_env {
        uint32_t days_remove_recovery;
    };

    typedef eosio::multi_index< N(recoverinfo), recovery_env > recovery_table;
    typedef eosio::singleton< N(recoveryenv), recovery_env > recovery_env_singleton;

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

        private: recovery_env_singleton m_recovery_env;
    };
}//recovery