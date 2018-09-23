<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid mb-3 py-5">
            <div class="container">
                <h1 class="display-6">
                Incoming Recovery Requests
                </h1>
                <p>
                Check and validate relationships recovery requests
                </p>
            </div>
            <!-- End of Jumbotron -->
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
                        <td class="align-middle">{{ row.username }}</td>
                        <td class="align-middle">
                            <div v-if="row.toDelete">
                                Deleted

                                <b-button variant="danger"
                                          class="mb-2"
                                >
                                    Undo
                                </b-button>
                            </div>

                            <b-button variant="danger"
                                      class="mb-2 mx-1"

                                      id="custom-button">
                                Discard
                            </b-button>
                            <b-button variant="success"
                                      class="mb-2 mx-1"

                                      id="custom-button">
                                Validate
                            </b-button>
                        </td>
                    </tr>

                    </tbody>
                </table>
            </div>
        </div>

    </main>
</template>

<script>
import {mapGetters, mapState} from 'vuex'
import EOS from 'eosjs'

    // @ is an alias to /src
    export default {
        name: 'Requests',

        data () {
            return {
                newUsername: null,
                newPermission: null,
                rows: [{
                    username: 'hkeoshkeosbp',
                    permission: 'active'
                }]
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

        created () {
            let eosjs = EOS({
                chainId: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca',
                httpEndpoint: 'https://api.jungle.alohaeos.com'
            })

            eosjs.getTableRows({
                json: true,
                code: 'lostorstolen',
                scope: 'lostorstolen',
                table: 'inrecovery',
                table_key: '',
                key_type: 'name',
                limit: 1
            }).then(({rows}) => {
                console.log(rows)
            })
        }
    }
</script>

<style>

</style>
