<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid mb-3 py-5">
            <div class="container">
                <h1 class="display-6" v-if="scatterAccount && scatterAccount.name">
                    {{ scatterAccount.name }}
                </h1>
                <p>
                    Setup your account recovery partners (2/3 + 1 to recover)
                </p>
            </div>
            <!-- End of jumbotron -->
        </div>
        <div class="container" id="main-wrapper-2">
            <div class="table-responsive">

                <table class="table">
                    <thead class="thead-dark">
                        <tr>
                            <th scope="col">#</th>
                            <th scope="col">Username</th>
                            <th scope="col">Actions</th>
                        </tr>
                    </thead>

                    <tbody>
                    <tr v-for="(row, index) in rows" :key="index">
                        <td class="align-middle">{{ index + 1 }}</td>
                        <td class="align-middle">{{ row }}</td>
                        <td class="align-middle">
                            <b-button variant="danger"
                                      class="mb-2"
                                      @click="deletePartner(index)"
                                      id="custom-button">
                                Delete Partner
                            </b-button>
                        </td>
                    </tr>

                    <tr>
                        <td>{{ rows.length + 1 }}</td>
                        <td>
                                <b-form-input v-model="newUsername"
                                              type="text"
                                              placeholder="Enter Username"
                                              required
                                              id="custom-input"
                                >
                                </b-form-input>
                        </td>
                        <td>
                            <b-button
                                    variant="success"
                                    class="mb-2"
                                    @click="addPartner"
                                    id="custom-button"
                            >
                                Add Partner
                            </b-button>
                        </td>
                    </tr>
                    </tbody>
                </table>
            </div>

            <b-button variant=""
                v-if="!scatterAccount || rows.length === 0"
                :disabled="!scatterAccount || rows.length === 0"
            >
                Add Recovery Partners
            </b-button>

            <b-button variant="success"
                      class="mb-2"
                      @click="savePartners"
                      id="custom-button"
                      v-else
            >
                Save recovery partners
            </b-button>
        </div>
    </main>
</template>

<script>
import EOS from 'eosjs'
import {mapGetters, mapState} from 'vuex'
import moment from 'moment'

export default {
  name: 'Partners',

  data () {
    return {
        newUsername: null,
        rows: [],
        lastSetTime: null
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

  watch: {
      scatterAccount: function(newScatterAccount, oldScatterAccount) {
          if (newScatterAccount && newScatterAccount.name) {
              this.updateAccounts()
          } else if (!newScatterAccount) {
              this.rows = null
          }
      }
  },

  methods: {
      parseDateTimestamp (timestamp) {
        return moment(timestamp)
      },

      updateAccounts () {
        let eosjs = EOS({
            chainId: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca',
            httpEndpoint: 'https://api.jungle.alohaeos.com'
        })

        eosjs.getTableRows({
            json: true,
            code: 'lostorstolen',
            scope: 'lostorstolen',
            table: 'recoverinfo',
            table_key: '',
            lower_bound: this.scatterAccount.name ? this.scatterAccount.name : '',
            key_type: 'name',
            limit: 1
        }).then(({rows}) => {
            let {backups, last_set_time, owner} = rows[0]

            if (this.scatterAccount.name === owner) {
                this.rows = backups
                this.lastSetTime = last_set_time 
            }
        })
      },

      addPartner () {
          if (this.newUsername) {
            this.rows.push(this.newUsername)
            this.newUsername = null
          }
      },

      deletePartner (index) {
          this.rows.splice(index, 1)
      },

      savePartners () {
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
            'lostorstolen',
            contract => {
                contract.setrecovery(this.scatterAccount.name, this.rows, "", options);
            }
        )
      }
  },

  beforeRouteEnter (to, from, next) {
    next(vm => {
        vm.updateAccounts()
    })
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

    #main-wrapper-2 {
        min-height: 520px;
    }

</style>
