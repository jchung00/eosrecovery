#pragma once
#include <eosio/testing/tester.hpp>

namespace eosio { namespace testing {

struct contracts {
   static std::vector<uint8_t> recovery_wasm() { return read_wasm("/Users/yepp4you/Work/blockchain/eosrecovery/recovery-backend/contracts/build/tests/../../recovery/bin/recovery/recovery.wasm"); }
   static std::string          recovery_wast() { return read_wast("/Users/yepp4you/Work/blockchain/eosrecovery/recovery-backend/contracts/build/tests/../../recovery/bin/recovery/recovery.wast"); }
   static std::vector<char>    recovery_abi() { return read_abi("/Users/yepp4you/Work/blockchain/eosrecovery/recovery-backend/contracts/build/tests/../../recovery/bin/recovery/recovery.abi"); }

   struct util {
      static std::vector<uint8_t> test_api_wasm() { return read_wasm("/Users/yepp4you/Work/blockchain/eosrecovery/recovery-backend/contracts/tests/test_contracts/test_api.wasm"); }
      static std::vector<uint8_t> exchange_wasm() { return read_wasm("/Users/yepp4you/Work/blockchain/eosrecovery/recovery-backend/contracts/tests/test_contracts/exchange.wasm"); }

      static std::vector<uint8_t> token_wasm() { return read_wasm("/Users/yepp4you/Work/blockchain/eosrecovery/recovery-backend/contracts/tests/test_contracts/eosio.token.wasm"); }
      static std::vector<char> token_abi() { return read_abi("/Users/yepp4you/Work/blockchain/eosrecovery/recovery-backend/contracts/tests/test_contracts/eosio.token.abi"); }
   };
};
}} //ns eosio::testing
