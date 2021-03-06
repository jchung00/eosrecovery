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
    using eosio::permission_level;

    const uint32_t seconds_per_day = 60 * 60 * 24;




    struct permission_level_weight {
        permission_level  permission;
        weight_type       weight;
    };

    struct key_weight {
        public_key key;
        weight_type     weight;
    };

    struct wait_weight {
        uint32_t     wait_sec;
        weight_type  weight;
    };
    struct authority {
        uint32_t                          threshold = 0;
        vector<key_weight>                keys;
        vector<permission_level_weight>   accounts;
        vector<wait_weight>               waits;
    };




    //@abi table
    struct recovery_info{
        account_name owner;
        vector<account_name> backups;
        uint64_t last_set_time;
        uint64_t primary_key() const { return owner; }
        EOSLIB_SERIALIZE( recovery_info, (owner)(backups)(last_set_time))
    };

    //@abi table
    struct in_recovery_inf{
        account_name owner;
        vector<account_name> backups;
        public_key new_key;
        uint64_t recover_start_time;
        vector<account_name> signed_recovery;
        vector<account_name> declined_recovery;
        uint64_t primary_key() const { return owner; }
        EOSLIB_SERIALIZE( in_recovery_inf, (owner)(backups)(new_key)(recover_start_time)(signed_recovery)(declined_recovery))
    };


    //@abi table
    struct recovery_env {
        uint64_t set_recovery_delay_time = 3*seconds_per_day;
        uint64_t reset_time = 7*seconds_per_day;
        EOSLIB_SERIALIZE( recovery_env, (set_recovery_delay_time)(reset_time));
    };

    typedef eosio::multi_index< N(recoverinfo), recovery_info > recovery_table;
    typedef eosio::multi_index< N(inrecovery), in_recovery_inf > in_recovery_table;
    //typedef eosio::multi_index< N(inremoval), in_removal_info > in_removal_table;
    typedef eosio::singleton< N(recoveryenv), recovery_env > recovery_env_singleton;

    class recovery_contract : public eosio::contract{
    public:
        explicit recovery_contract(action_name self);

        //@abi action
        void setenv(uint64_t set_recovery_delay_time, uint64_t reset_time);

        //@abi action
        void setrecovery(account_name owner, const vector<account_name>& backups, const string& cell_hash);

        //@abi action
        void chgrecovery(account_name owner, const vector<account_name>& backups);

        //@abi action
        void recover(account_name owner, account_name recoverer, const public_key& new_key, bool agree);

        void reset(account_name owner, const public_key& new_key);

    private: recovery_env_singleton m_recovery_env;
    };
}//recovery
