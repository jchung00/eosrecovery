#include <recovery/recovery.hpp>

namespace recovery{
    recovery_contract::recovery_contract(action_name self) : contract(self), m_recovery_env(self, self) {
        if (m_recovery_env.exists() == false) {
            m_recovery_env.set( recovery_env(), _self );
        }
    }

    //@abi action
    void recovery_contract::setenv(uint64_t set_recovery_delay_time, uint64_t reset_time) {
        require_auth(_self);

        eosio_assert(set_recovery_delay_time >= 1 && set_recovery_delay_time <= 30, "Invalid delay time.");

        auto recovery_env = m_recovery_env.get();

        recovery_env.set_recovery_delay_time = set_recovery_delay_time;
        recovery_env.reset_time = reset_time;

        m_recovery_env.set( recovery_env, _self );
    }

    //@abi action
    void recovery_contract::setrecovery(account_name owner, const vector<account_name>& backups, const string& cell_hash){
        require_auth(owner);

        eosio_assert(backups.size()>=2, "There should be at least 2 recovery accounts set up.");
        eosio_assert(cell_hash.size()<1024, "Cell hash is too large");

        recovery_table recovery_accounts(_self, _self);
        auto itr = recovery_accounts.find(owner);

        for(int i=0; i<backups.size(); i++){
            eosio_assert(is_account(backups.at(i)), "Invalid recovery account.");
        }

        auto recovery_env = m_recovery_env.get();
        auto current_time = now();

        if(itr==recovery_accounts.end()){
            recovery_accounts.emplace(_self, [&](auto& recovery_info){
                recovery_info.owner = owner;
                recovery_info.backups = backups;
                recovery_info.last_set_time = current_time;
            });
        }

        else{
            recovery_accounts.modify(itr, 0, [&](auto& recovery_info){
                recovery_info.last_set_time = current_time;
            });

            // Transaction
            transaction out{};

            out.actions.emplace_back(eosio::permission_level {owner, N(owner)},
                                     _self,
                                     N(chgrecovery),
                                     std::make_tuple(owner,
                                                     backups)
            );
            out.delay_sec = recovery_env.set_recovery_delay_time;
            cancel_deferred(owner);
            out.send(owner, owner, true);
        }
    }

    //@abi action
    void recovery_contract::chgrecovery(account_name owner, const vector<account_name>& backups){
        require_auth(owner);

        recovery_table recovery_accounts(_self, _self);
        auto itr = recovery_accounts.find(owner);
        eosio_assert(itr != recovery_accounts.end(), "Account does not have recovery set up.");

        auto current_time = now();
        auto recovery_env = m_recovery_env.get();

        eosio_assert(current_time - (*itr).last_set_time > recovery_env.set_recovery_delay_time && (*itr).last_set_time != -1,
                     "Change recovery time has not been exceeded.");

        recovery_accounts.modify(itr, 0, [&](auto& recovery_info){
            recovery_info.backups = backups;
            recovery_info.last_set_time = -1;
        });
    }

    //@abi action
    void recovery_contract::recover(account_name owner, account_name recoverer, const public_key& new_key, bool agree){
        require_auth(recoverer);
        eosio_assert(is_account(owner), "Non-existent account.");
        eosio_assert( new_key != eosio::public_key(), "Public key should not be the default value" );

        recovery_table recovery_accounts(_self, _self);
        auto itr = recovery_accounts.find(owner);
        eosio_assert(itr!=recovery_accounts.end(), "Account does not have recovery set up.");

        auto itr_backup = std::find((*itr).backups.begin(), (*itr).backups.end(), recoverer);
        eosio_assert(itr_backup != (*itr).backups.end(), "Account is not registered as one of the fallbacks.");

        in_recovery_table in_recovery(_self, _self);
        auto itr_account = in_recovery.find(owner);

        auto current_time = now();

        if(itr_account == in_recovery.end()){
            if(agree) {
                in_recovery.emplace(_self, [&](auto& in_recovery_info
                ){
                    in_recovery_info.owner = owner;
                    in_recovery_info.backups = (*itr).backups;
                    in_recovery_info.new_key = new_key;
                    in_recovery_info.recover_start_time = current_time;

                    in_recovery_info.signed_recovery.push_back(recoverer);
                });
            } else {
                in_recovery.emplace(_self, [&](auto& in_recovery_info){
                    in_recovery_info.owner = owner;
                    in_recovery_info.backups = (*itr).backups;
                    in_recovery_info.new_key = new_key;
                    in_recovery_info.recover_start_time = current_time;

                    in_recovery_info.declined_recovery.push_back(recoverer);
                });
            }
        }

        else{
            uint64_t time_since_recover_start = current_time - (*itr_account).recover_start_time;

            eosio_assert(new_key == (*itr_account).new_key, "Proposed public key is not the same.");

            auto itr_signed = std::find((*itr_account).signed_recovery.begin(), (*itr_account).signed_recovery.end(), recoverer);

            eosio_assert(itr_signed == (*itr_account).signed_recovery.end(), "Recoverer has already signed.");

            auto itr_declined = std::find((*itr_account).declined_recovery.begin(), (*itr_account).declined_recovery.end(), recoverer);

            eosio_assert(itr_declined == (*itr_account).declined_recovery.end(), "Recoverer has already declined.");

            if(time_since_recover_start >= seconds_per_day){
                in_recovery.erase(itr_account);
            }
            else{
                if(agree) {
                    in_recovery.modify(itr_account, _self, [&](auto& in_recovery_info) {
                        in_recovery_info.signed_recovery.push_back(recoverer);
                    });

                    if((*itr_account).signed_recovery.size() >= (((*itr_account).backups.size() * 2) / 3) + 1){
                        authority auth{ 1, {{new_key, 1}}, {}, {} };

                        eosio::action(eosio::permission_level{owner, N(owner)},
                                      N(eosio),
                                      N(updateauth),
                                      std::make_tuple( owner,
                                                       N(active),
                                                       N(owner),
                                                       auth))
                                      .send();

                        in_recovery.erase(itr_account);
                    }
                }
                else{
                    in_recovery.modify(itr_account, _self, [&](auto& in_recovery_info) {
                        in_recovery_info.signed_recovery.push_back(recoverer);
                    });

                    if((*itr_account).declined_recovery.size() >= (((*itr_account).backups.size() * 2) / 3) + 1){
                        in_recovery.erase(itr_account);
                    }
                }
            }
        }
    }

    //@abi action
    void recovery_contract::reset(account_name owner, const public_key& new_key) {
        require_auth(owner);

        eosio_assert( new_key != eosio::public_key(), "Public key should not be the default value" );

        auto recovery_env = m_recovery_env.get();

        // Transaction
        transaction out{};

        authority auth{ 1, {{new_key, 1}}, {}, {} };

        out.actions.emplace_back(eosio::permission_level {owner, N(owner)},
                                 N(eosio),
                                 N(updateauth),
                                 std::make_tuple(owner, N(active), N(owner), auth));
        out.delay_sec = recovery_env.reset_time;
        cancel_deferred(owner);
        out.send(owner, owner, true);
    }
} //recovery

EOSIO_ABI( recovery::recovery_contract, (setenv)(setrecovery)(chgrecovery)(recover)(reset))
