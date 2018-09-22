#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/types.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/contract.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/public_key.hpp>
#include <eosiolib/transaction.hpp>

#include <string>
#include <vector>
#include <algorithm>

namespace recovery {
    using std::string;
    using std::vector;
    using std::set;

    using eosio::public_key;
    using eosio::asset;
    using eosio::transaction;

    const uint32_t seconds_per_day = 60 * 60 * 24;

    //@abi table
    struct recovery_info{
        account_name owner;
        vector<account_name> backups;
        //string cell_hash;
        uint64_t last_set_time;
        //uint64_t rmv_recovery_start_time;
        //uint64_t recover_start_time;
        uint64_t primary_key() const { return owner; }
        EOSLIB_SERIALIZE( recovery_info, (owner)(backups)/*(cell_hash)*/(last_set_time)/*(rmv_recovery_start_time)(recover_start_time)*/ )
    };

    //@abi table
    struct in_recovery_info{
        account_name owner;
        vector<account_name> backups;
        public_key new_key;
        //string cell_hash;
        uint64_t recover_start_time;
        vector<account_name> signed_recovery;
        vector<account_name> declined_recovery;
        uint64_t primary_key() const { return owner; }
        EOSLIB_SERIALIZE( in_recovery_info, (owner)(backups)(new_key)/*(cell_hash)*/(recover_start_time)(signed_recovery)(declined_recovery))
    };

    /*
    //@abi table
    struct in_removal_info{
        account_name owner;
        vector<account_name> backups;
        string cell_hash;
        uint64_t recover_start_time;
        vector<account_name> agreed;
        vector<account_name> disagreed;
        uint64_t primary_key() const { return owner; }
        EOSLIB_SERIALIZE( in_recovery_info, (owner)(backups)(cell_hash)(recover_start_time)(agreed)(disagreed))
    };
     */

    //@abi table
    struct recovery_env {
        uint32_t set_recovery_delay_time = 10;
        EOSLIB_SERIALIZE( recovery_env, (set_recovery_delay_time));
    };

    typedef eosio::multi_index< N(recoverinfo), recovery_info > recovery_table;
    typedef eosio::multi_index< N(inrecovery), in_recovery_info > in_recovery_table;
    //typedef eosio::multi_index< N(inremoval), in_removal_info > in_removal_table;
    typedef eosio::singleton< N(recoveryenv), recovery_env > recovery_env_singleton;

    class recovery_contract : public eosio::contract{
        public:
            explicit recovery_contract(action_name self);

            //@abi action
            void setenv(uint32_t set_recovery_delay_time){

            }

            //@abi action
            void setrecovery(account_name owner, const vector<account_name>& backups, const string& cell_hash){
            }

            //@abi action
            void chgrecovery(account_name owner){
            }

            //@abi action
            void recover(account_name owner, account_name recoverer, const public_key& new_key, bool agree){
            }

        private: recovery_env_singleton m_recovery_env;
    };
}//recovery