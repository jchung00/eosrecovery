<template>
  <main role="main">
    <div class="jumbotron">
      <div class="container">
        <img src="@/assets/eosar-logo-icon.svg" class="mb-4" id="icon-logo">
        <h1 class="display-6 mb-2">
          EOS Account Recovery
        </h1>
        <p class="mb-5">
        Don't lose an account ever again, secure it via trusted eos.io relationships.
        </p>
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

      <!-- End of jumbotron -->
    </div>
      <div class="container">
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
    min-height: 90vh;
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
