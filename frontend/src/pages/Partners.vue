<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid mb-3 py-5">
            <div class="container">
                <h1 class="display-6">
                Account Name here
                </h1>
                <p>
<<<<<<< HEAD
                    Setup your account recovery partners (2/3 + 1 to recover)
=======
                Setup your account recovery partners
>>>>>>> 0951df7b71b59bcf05748d9bc04a126894cd5c30
                </p>
            </div>
            <!-- End of jumbotron -->
        </div>
        <div class="container">
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
                                <input v-model="newUsername" required/>
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

            <b-button variant="success"
                      class="mb-2"
                      @click="savePartners"
                      id="custom-button"
            >
                Save recovery partners
            </b-button>
        </div>
    </main>
</template>

<script>
import EOS from 'eosjs'
import {mapGetters} from 'vuex'

export default {
  name: 'Partners',

  data () {
    return {
        newUsername: null,
        rows: []
    }
  },

  computed: {
    ...mapGetters({
      scatterAccount: 'scatter/scatterAccount'
    })
  },

  methods: {
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
            port: 80,
            protocol: 'http',
            host: 'api.jungle.alohaeos.com',
            httpEndpoint: 'http://api.jungle.alohaeos.com'
        }, EOS)

        eosjs.transaction(
            'forgoteoskey', 
            contract => {
                contract.setrecovery(this.scatterAccount, this.rows, "");
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
