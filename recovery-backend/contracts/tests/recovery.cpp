#include "test.hpp"

class recovery_tester : public tester {
public:
   recovery_tester() {
    create_accounts( {/*N(eosio.token),*/ N(eosrecovery1)} );
    produce_block();
    create_accounts( {N(useraaaaaaaa), N(recoveraaaaa),  N(recoveraaaab),  N(recoveraaaac)} );
    produce_block();

/*
    base_tester::push_action(config::system_account_name, N(setpriv), config::system_account_name,
      mutable_variant_object()
      ("account", "eosio.token")
      ("is_priv", 1)
    );

    set_code( N(eosio.token), contracts::util::token_wasm() );
    set_abi( N(eosio.token), contracts::util::token_abi().data() );
*/

    set_code( N(eosrecovery1), contracts::recovery_wasm() );
    set_abi( N(eosrecovery1), contracts::recovery_abi().data() );

    produce_blocks();

    const auto& accnt = control->db().get<account_object,by_name>( N(eosrecovery1) );
    abi_def abi;
    BOOST_REQUIRE_EQUAL(abi_serializer::to_abi(accnt.abi, abi), true);
    abi_ser.set_abi(abi, fc::seconds(1));
   }

/*
  bool get_record(xxx& record, account_name owner) {
    return get_table_entry(record, N(eosrecovery1), N(eosrecovery1), N(records), owner);
  }
*/

  abi_serializer abi_ser;
};

BOOST_AUTO_TEST_SUITE(recovery_tests)

BOOST_FIXTURE_TEST_CASE( setrecovery, recovery_tester ) try {
  std::vector<account_name> backups{N(recoveraaaaa), N(recoveraaaab), N(recoveraaaac)};

  auto req = mvo()
      ("owner",  "useraaaaaaaa")
      ("backups", backups)
      ("cell_hash", "xxxxxxxxxxxxxxxxxxxxxxxxxxxx");

   set_authority("useraaaaaaaa", "owner", authority(1,
      vector<key_weight>{{get_private_key("useraaaaaaaa", "owner").get_public_key(), 1}},
      vector<permission_level_weight>{{{N(eosrecovery1), "eosio.code"}, 1}}), "",
      { { "useraaaaaaaa", "owner" } }, { get_private_key( "useraaaaaaaa", "owner" ) });

  auto trace = base_tester::push_action( N(eosrecovery1), N(setrecovery), N(useraaaaaaaa), req);
  produce_block();
  trace = base_tester::push_action( N(eosrecovery1), N(setrecovery), N(useraaaaaaaa), req);
  produce_block();

  /*
  record_t r_gameuseraaaa;
  auto trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaaa), record1_1);
  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaaa), record1_2);
  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaaa), record1_3);

  get_record(r_gameuseraaaa, N(gameuseraaaa));
  //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(r_gameuseraaaa) );
  musicscore_t mscore1_3{static_cast<uint16_t>(record1_3["music_id"].as_uint64()),  static_cast<uint32_t>(record1_3["score"].as_uint64())};
  auto itr1_3 = std::find(r_gameuseraaaa.scores.begin(),r_gameuseraaaa.scores.end(), mscore1_3);
  BOOST_CHECK(record1_3["score"] == itr1_3->score);

  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaaa), record1_3_2);
  get_record(r_gameuseraaaa, N(gameuseraaaa));
  //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(r_gameuseraaaa) );
  musicscore_t mscore1_3_2{static_cast<uint16_t>(record1_3_2["music_id"].as_uint64()),  static_cast<uint32_t>(record1_3_2["score"].as_uint64())};
  auto itr1_3_2 = std::find(r_gameuseraaaa.scores.begin(),r_gameuseraaaa.scores.end(), mscore1_3_2);
  BOOST_CHECK( itr1_3_2 != r_gameuseraaaa.scores.end());
  BOOST_CHECK(record1_3_2["score"] == itr1_3_2->score);

  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaaa), record1_3_3);
  get_record(r_gameuseraaaa, N(gameuseraaaa));
  //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(r_gameuseraaaa) );
  musicscore_t mscore1_3_3{static_cast<uint16_t>(record1_3_3["music_id"].as_uint64()),  static_cast<uint32_t>(record1_3_3["score"].as_uint64())};
  auto itr1_3_3 = std::find(r_gameuseraaaa.scores.begin(),r_gameuseraaaa.scores.end(), mscore1_3_3);
  BOOST_CHECK( itr1_3_3 != r_gameuseraaaa.scores.end());
  BOOST_CHECK(record1_3_3["score"] == itr1_3_3->score);

  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaab), record2_1);
  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaab), record2_2);
  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaab), record2_3);

  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaac), record3_1);
  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaac), record3_2);
  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaac), record3_3);

  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaad), record4_1);
  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaad), record4_2);
  produce_block();
  trace = base_tester::push_action( N(eoseoultwcvr), N(regrecord), N(gameuseraaad), record4_3);

  record_t r_gameuseraaad;
  get_record(r_gameuseraaad, N(gameuseraaad));
  //BOOST_TEST_MESSAGE( fc::json::to_pretty_string(r_gameuseraaad) );
  musicscore_t mscore4_3{static_cast<uint16_t>(record4_3["music_id"].as_uint64()),  static_cast<uint32_t>(record4_3["score"].as_uint64())};
  auto itr4_3 = std::find(r_gameuseraaad.scores.begin(),r_gameuseraaad.scores.end(), mscore4_3);
  BOOST_CHECK(itr4_3 != r_gameuseraaad.scores.end());
  BOOST_CHECK(record4_3["score"] == itr4_3->score);
  */
} FC_LOG_AND_RETHROW()

BOOST_AUTO_TEST_SUITE_END()
