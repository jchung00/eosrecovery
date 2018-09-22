<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid">
            <div class="container">
                <h1 class="display-6">
                    Account Name here
                </h1>
                <p>
                    Setup your account recovery partners
                </p>
            </div>
            <!-- End of jumbotron -->
        </div>
        <div>
            <h3>Existing Recovery Partners</h3>
            <div>
                <table class="table">
                    <thead>
                    <tr>
                        <th scope="col">#</th>
                        <th scope="col">First</th>
                        <th scope="col">Last</th>
                        <th scope="col">Handle</th>
                    </tr>
                    </thead>
                    <tbody>
                    <tr>
                        <th scope="row">1</th>
                        <td>Mark</td>
                        <td>Otto</td>
                        <td>
                            <b-button
                                variant="danger"
                                class="mb-2"
                            >Delete Partner
                            </b-button>
                        </td>
                    </tr>
                    <tr>
                        <th scope="row">2</th>
                        <td>Jacob</td>
                        <td>Thornton</td>
                        <td>
                            <b-button
                                variant="danger"
                                class="mb-2"
                        >Delete Partner
                        </b-button>
                        </td>
                    </tr>
                    <tr>
                        <th scope="row">3</th>
                        <td>Larry</td>
                        <td>the Bird</td>
                        <td>
                            <b-button
                                variant="danger"
                                class="mb-2"
                            >Delete Partner
                        </b-button>
                        </td>
                    </tr>
                    </tbody>
                </table>
                

                <b-button
                        variant="success"
                        class="mb-2"
                >Add recovery Partner</b-button>
            </div>
        </div>
    </main>
</template>

<script>
    // @ is an alias to /src
export default {
  name: 'Recovery',

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
