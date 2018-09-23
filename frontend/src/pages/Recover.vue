<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid py-5">
            <div class="container">
                <h1 class="display-6">
                Recovery Console
                </h1>
                <p>
                Initiate account recovery process
                </p>
            </div>
        </div>

        <div class="container mb-4">
            <div class="row">
                <div class="col">

                </div>

                <div class="col-md-6">
                    <b-form @submit="onSubmit" @reset="onReset" v-if="show">

                        <b-form-group id="accountRecovery"
                                      label="Scatter Account Name"
                                      label-for="accountName"
                                      class="text-left"
                                      >
                            <b-form-input id="accountName"
                                          type="text"
                                          v-model="form.account"
                                          required
                                          placeholder="Enter Account Name">
                            </b-form-input>
                        </b-form-group>

                        <b-form-group id="exampleInputGroup2"
                                      label="EOS Account Name"
                                      label-for="exampleInput2"
                                      required
                                      class="text-left"
                                      >
                            <b-form-input id="exampleInput2"
                                          type="text"
                                          v-model="form.eosAccount"
                                          required
                                          placeholder="Enter EOS Account Name">
                            </b-form-input>
                        </b-form-group>

                        <b-form-group id="exampleInputGroup2"
                                      label="Public Key"
                                      label-for="publicKey"
                                      required
                                      class="text-left"
                                      >
                            <b-form-input id="exampleInput2"
                                          type="text"
                                          v-model="form.publicKey"
                                          required
                                          placeholder="Enter Public Key">
                            </b-form-input>
                        </b-form-group>

                        <b-button type="submit" variant="primary" class="mx-2" id="custom-button">Submit and Recover Account</b-button>
                        <b-button type="reset" variant="danger" class="mx-2" id="custom-button">Reset</b-button>
                    </b-form>
                </div>

                <div class="col">
                </div>
            </div>


        </div>

    </main>
</template>

<script>
export default {
  name: 'Recover',

  data () {
    return {
        show: true,
        form: {
            account: null,
            eosAccount: null,
            publicKey: null
        }
    }
  },

  methods: {
    recover () {

    }
  }
}
</script>

<style>
    html, body {
        height: 100%;
    }
    .main {
        margin: 0 auto;
        height: 100%;
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
