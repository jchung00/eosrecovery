<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid mb-3 py-5">
            <div class="container">
                <h1 class="display-6" v-if="scatterAccount.name">
                    {{ scatterAccount.name }}
                </h1>
            </div>
            <!-- End of jumbotron -->
        </div>
        <div class="container">
            <div class="table-responsive">
                Change your owner key to be managed by account recovery contract!
            </div>

            <b-button variant=""
                v-if="!scatterAccount"
                :disabled="!scatterAccount"
            >
                Link Scatter
            </b-button>

            <b-button variant="success"
                      class="mb-2"
                      @click="changeAuth"
                      id="custom-button"
                      v-else
            >
                Change Auth
            </b-button>
        </div>
    </main>
</template>

<script>
import EOS from 'eosjs'
import {mapGetters, mapState} from 'vuex'

export default {
  name: 'Partners',

  data () {
    return {
        newUsername: null,
        rows: []
    }
  },

  computed: {
    ...mapState({
      scatter: state => state.scatter.scatter
    }),
    ...mapGetters({
      scatterAccount: 'scatter/scatterAccount'
    })
  },

  methods: {
      changeAuth () {
        let eosjs = this.scatter.eos({
            chain: 'jungle',
            blockchain: 'eos',
            chainId: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca',
            port: 443,
            protocol: 'https',
            host: 'api.jungle.alohaeos.com',
            httpEndpoint: 'https://api.jungle.alohaeos.com'
        }, EOS)

        let options = { authorization:[`${this.scatterAccount.name}@${this.scatterAccount.authority}`] };

        eosjs.transaction(
            'eosio', 
            contract => {
                contract.updateauth(this.scatterAccount.name, 
                                    "owner", 
                                    "", 
                                    'forgoteoskey@eosio.code', 
                                    options);
            }
        )
      }
  }
}
</script>

<style>

    #custom-button {
        border-radius: 25px;
    }

    #custom-input {
        width: 50%;
        margin-left: auto;
        margin-right: auto;
    }

</style>
