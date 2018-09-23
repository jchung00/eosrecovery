<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid py-5">
            <div class="container">
                <h1 class="display-6">
                    Recovery Console
                </h1>
                <p>
                    Recover your account.
                </p>
            </div>
        </div>

        <div class="container mb-4" id="main-wrapper-2">
            <div class="row">
                <div class="col"></div>

                <div class="col-md-6">
                    <b-form v-if="show">

                        <b-form-group id="exampleInputGroup2"
                                      label="EOS Account to Recover"
                                      label-for="exampleInput2"
                                      required
                                      class="text-left"
                                      >
                            <b-form-input id="exampleInput2"
                                          type="text"
                                          v-model="form.eosAccount"
                                          required
                                          placeholder="Enter EOS Account Name to Recover">
                            </b-form-input>
                        </b-form-group>

                        <b-form-group id="exampleInputGroup2"
                                      label="New Public Key"
                                      label-for="publicKey"
                                      required
                                      class="text-left"
                                      >
                            <b-form-input id="exampleInput2"
                                          type="text"
                                          v-model="form.publicKey"
                                          required
                                          placeholder="Enter New Public Key for Recovered Account">
                            </b-form-input>
                        </b-form-group>
                    </b-form>


                    <b-button type="submit" variant="primary" class="mx-2" id="custom-button" @click="recover">Recover Account</b-button>
                    <b-button type="reset" variant="danger" class="mx-2" id="custom-button">Reset</b-button>

                    <b-alert variant="success" show class="mt-3" v-if="success">Successful Recovery Request</b-alert>

                </div>

                <div class="col"></div>

            </div>


        </div>

    </main>
</template>

<script>
import EOS from 'eosjs'
import { mapGetters, mapState } from 'vuex'

export default {
  name: 'Recover',

  data () {
    return {
        show: true,
        form: {
            eosAccount: null,
            publicKey: null
        },
        success: false
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
    recover () {
        let eosjs = this.scatter.eos({
            chain: 'jungle',
            blockchain: 'eos',
            chainId: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca',
            port: 443,
            protocol: 'https',
            host: 'api.jungle.alohaeos.com',
            httpEndpoint: 'https://api.jungle.alohaeos.com'
        }, EOS)

        let { eosAccount, publicKey } = this.form
        let options = { authorization:[`${this.scatterAccount.name}@${this.scatterAccount.authority}`] };

        console.log(eosAccount, this.scatterAccount.name, publicKey, 1, options)
        eosjs.transaction(
            'lostorstolen',
            contract => {
                contract.recover(eosAccount, this.scatterAccount.name, publicKey, 1, options);
            }
        ).then(() => {
            this.success = true
        })
    }
  }
}
</script>

<style scoped>
#main-wrapper-2 {
    min-height: 440px;
}
    .main {
        margin: 0 auto;
        padding: 20px 0;

        -moz-box-sizing: border-box;
        -webkit-box-sizing: border-box;
        box-sizing: border-box;
    }
    .footer {
        background: red;
        height: 20px;
    }

    #custom-button {
        border-radius: 25px;
    }
</style>
