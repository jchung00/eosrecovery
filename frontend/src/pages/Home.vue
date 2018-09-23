<template>
  <main role="main">
    <div class="jumbotron">
      <div class="container">
        <img src="@/assets/eosar-logo-icon.svg" class="mb-4" id="icon-logo">
        <h1 class="display-6 mb-2">
          EOS Account Recovery
        </h1>

        <p class="mb-5">
          Don't lose an account ever again, secure it via trusted EOS contracts.
        </p>

        <b-button
                variant="success"
                size="lg"
                id="custom-button"
                class="mx-2"
                v-if="!scatter">
            Download Scatter
        </b-button>

        <b-button
                variant="success"
                size="lg"
                id="custom-button"
                class="mx-2"
                @click="linkIdentity"
                v-if="scatter && !identity">
            Link Scatter
        </b-button>

        <b-button
                variant="success"
                size="lg"
                id="custom-button"
                class="mx-2"
                @click="initialize"
                v-if="scatter && identity && !permissions">
            Initialize Contract
        </b-button>

        <div v-if="scatter && identity && permissions">
          <b-button
                  variant="success"
                  size="lg"
                  id="custom-button"
                  class="mx-2"
                  to="partners">
              Manage Partners
          </b-button>
          <b-button
                  variant="light"
                  size="lg"
                  id="custom-button"
                  class="mx-2"
                  to="recover">
              Recover Account
          </b-button>
        </div>
      </div>

      <!-- End of jumbotron -->
    </div>
      <div class="container" id="main-wrapper">
          <!--This is the Added Value section, present EOS Hong Kong with 3 different added values-->
          <div class="row">
              <div class="col-lg-4">
                  <div class="thumbnail text-center">
                      <img src="@/assets/ledger.svg">
                      <h3>Property</h3>
                      <div class="caption">
                          <p>Your account is yours forever</p>
                      </div>
                  </div>
              </div>

              <div class="col-lg-4">
                  <div class="thumbnail text-center">
                      <img src="@/assets/encryption.svg">
                      <h3>Security</h3>
                      <div class="caption">
                          <p>Social proof via trusted relationships</p>
                      </div>
                  </div>
              </div>

              <div class="col-lg-4">
                  <div class="thumbnail text-center">
                      <img src="@/assets/wallet.svg">
                      <h3>Recovery</h3>
                      <div class="caption">
                          <p>Retrieve your funds in any cases</p>
                      </div>
                  </div>
              </div>

              <!--End of Row-->
          </div>
          <!--End of Values Container-->
      </div>
  </main>
</template>


<script>
import EOS from 'eosjs'
import {mapGetters, mapState, mapActions} from 'vuex'

export default {
  name: 'Home',

  data () {
    return {
      account: null
    }
  },

  watch: {
      scatterAccount: function(newScatterAccount, oldScatterAccount) {
          if (newScatterAccount && newScatterAccount.name) {
            this.updateAccount()
          }
      }
  },

  computed: {
    ...mapState({
      scatter: state => state.scatter.scatter
    }),
    ...mapGetters({
      identity: 'scatter/scatterIdentity',
      scatterAccount: 'scatter/scatterAccount'
    }),
    permissions () {
      if (!this.account) return null

      let owner = this.account.permissions.find(permission => permission.perm_name === 'owner')

      if(!owner) return null

      let lostorstolen = owner.required_auth.accounts.find(({permission}) => permission.actor === 'lostorstolen' && permission.permission === 'eosio.code')
      
      if(!lostorstolen) return null

      return lostorstolen
    }
  },
  
  methods: {
    ...mapActions({
      linkIdentity: 'scatter/LINK_IDENTITY'
    }),

    updateAccount () {  
      if (!this.scatterAccount || !this.scatterAccount.name) return     
      let eosjs = EOS({
          chainId: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca',
          httpEndpoint: 'https://api.jungle.alohaeos.com'
      })
      
      eosjs.getAccount(this.scatterAccount.name).then(account => {
        this.account = account
      })
    },

    initialize () {
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
                                  'lostorstolen@eosio.code', 
                                  options);
          }
      ).then(() => {
        this.updateAccount()
      })
    }
  },
  mounted () {
    this.updateAccount()
  }
}
</script>

<style>
.jumbotron {
    background: #41295a;  /* fallback for old browsers */
    background: -webkit-linear-gradient(to right, #2F0743, #41295a);  /* Chrome 10-25, Safari 5.1-6 */
    background: linear-gradient(to right, #2F0743, #41295a); /* W3C, IE 10+/ Edge, Firefox 16+, Chrome 26+, Opera 12+, Safari 7+ */
    /* Font */
    color: white;
    border-radius: 0 !important;
}

#main-wrapper {
    width: 100%;
    padding-left: 0;
    padding-right: 0;
    margin-top: 60px;
    min-height: 228px;
}

#custom-button {
    border-radius: 25px;
}

#icon-logo {
    height: 100px;
}

@font-face {
    font-family: Roboto;
    src: url(https://fonts.googleapis.com/css?family=Roboto) format("opentype");
}

body {
    font-family: Roboto;
}

</style>
