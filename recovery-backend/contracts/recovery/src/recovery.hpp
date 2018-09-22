#pragma once

#include <eosiolib/types.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/public_key.hpp>

#include <string>
#include <vector>
#include <algorithm>

namespace recovery {
    using std::string;
    using std::vector;
    using std::set;

    using eosio::public_key;
    using eosio::asset;

    const uint32_t seconds_per_day = 60 * 60 * 24;

    //@abi table
    struct recovery_info{
        account_name owner;
        vector<account_name> backups;
        string cell_hash;
        //uint64_t rmv_recovery_start_time;
        //uint64_t recover_start_time;
        uint64_t primary_key() const { return owner; }
        EOSLIB_SERIALIZE( recovery_info, (owner)(backups)(cell_hash)/*(rmv_recovery_start_time)(recover_start_time)*/ )
    };

    //@abi table
    struct in_recovery_info{
        account_name owner;
        vector<account_name> backups;
        string cell_hash;
        uint64_t recover_start_time;
        vector<account_name> signed_recovery;
        vector<account_name> declined_recovery;
        uint64_t primary_key() const { return owner; }
        EOSLIB_SERIALIZE( in_recovery_info, (owner)(backups)(cell_hash)(recover_start_time)(signed_recovery)(decline_recovery))
    };

    //@abi table
    struct recovery_env {
        uint32_t days_remove_recovery;
        EOSLIB_SERIALIZE( recovery_env, (days_remove_recovery));
    };

    typedef eosio::multi_index< N(recoverinfo), recovery_info > recovery_table;
    typedef eosio::multi_index< N(inrecovery), in_recovery_info > in_recovery_table;
    typedef eosio::singleton< N(recoveryenv), recovery_env > recovery_env_singleton;

    class recovery_contract : public eosio::contract{
        public:
            explicit recovery_contract(action_name self);

            //@abi action
            void addrecovery(account_name owner, const vector<account_name>& backups, const string& cell_hash){
            }

            //@abi action
            void rmvrecovery(account_name owner){
            }

            //@abi action
            void recover(account_name owner, account_name requester, const public_key& new_key){
            }

        private: recovery_env_singleton m_recovery_env;
    };
}//recovery