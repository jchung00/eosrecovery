<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid">
            <div class="container">
                <h1 class="display-6">
                    Recovery Console
                </h1>

                <p>
                    Recover an account
                </p>
            </div>
        </div>

        <b-button variant="success"
                  class="mb-2"
                  @click="recover" >
            Recover Account
        </b-button>
    </main>
</template>

<script>
export default {
  name: 'Recover',

  data () {
    return {

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
</style>
