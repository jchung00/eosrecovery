#include <boost/test/unit_test.hpp>

#include <eosio/testing/tester.hpp>
#include <eosio/chain/abi_serializer.hpp>
#include <eosio/chain/wast_to_wasm.hpp>

#include <fc/variant_object.hpp>

#include <Runtime/Runtime.h>

#include "contracts.hpp"

// #include <eosiolib/types.h>

using namespace eosio::testing;
using namespace eosio;
using namespace eosio::chain;
using namespace eosio::testing;
using namespace fc;

using mvo = fc::mutable_variant_object;

typedef uint16_t weight_type;
struct public_key {
   char data[34];
};

struct permission_level_weight_t {
    permission_level  permission;
    weight_type       weight;

    // explicit serialization macro is not necessary, used here only to improve compilation time
};
FC_REFLECT( permission_level_weight_t, (permission)(weight) )

struct key_weight_t {
    public_key   key;
    weight_type  weight;

    // explicit serialization macro is not necessary, used here only to improve compilation time
};
FC_REFLECT( key_weight_t, (key)(weight) )

struct authority_t {
    uint32_t                              threshold;
    uint32_t                              delay_sec;
    std::vector<key_weight>               keys;
    std::vector<permission_level_weight>  accounts;

    // explicit serialization macro is not necessary, used here only to improve compilation time
};
FC_REFLECT( authority_t, (threshold)(delay_sec)(keys)(accounts) )
/* SYED */


//@abi table
struct recovery_info_t {
    account_name owner;
    vector<account_name> backups;
    //string cell_hash;
    uint64_t last_set_time;
    //uint64_t rmv_recovery_start_time;
    //uint64_t recover_start_time;
    uint64_t primary_key() const { return owner; }
};
FC_REFLECT( recovery_info_t, (owner)(backups)/*(cell_hash)*/(last_set_time)/*(rmv_recovery_start_time)(recover_start_time)*/ )

//@abi table
struct in_recovery_inf_t {
    account_name owner;
    vector<account_name> backups;
    public_key new_key;
    //string cell_hash;
    uint64_t recover_start_time;
    vector<account_name> signed_recovery;
    vector<account_name> declined_recovery;
    uint64_t primary_key() const { return owner; }
};
FC_REFLECT( in_recovery_inf_t, (owner)(backups)(new_key)/*(cell_hash)*/(recover_start_time)(signed_recovery)(declined_recovery))

//@abi table
struct recovery_env_t {
    uint64_t set_recovery_delay_time = 10;
};
FC_REFLECT( recovery_env_t, (set_recovery_delay_time));