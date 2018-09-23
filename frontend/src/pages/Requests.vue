<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid mb-3 py-5">
            <div class="container">
                <h1 class="display-6">
                 Recovery Requests
                </h1>
                <p>
                Check and validate incoming and outgoing recovery requests
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
                        <th scope="col">Owner</th>
                        <th scope="col">Signed Recovery</th>
                        <th scope="col">Requested</th>
                        <th scope="col">Request Time</th>
                    </tr>
                    </thead>

                    <tbody>
                    <tr v-for="(row, index) in rows" :key="index">
                        <td class="align-middle">{{ index + 1 }}</td>
                        <td class="align-middle">{{ row.owner }}</td>
                        <td class="align-middle">{{ row.signed_recover }}</td>
                        <td class="align-middle">{{ row.backups }}</td>
                        <td class="align-middle">{{ row.recover_start_time }}</td>
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

    export default {
        name: 'Requests',

        data () {
            return {
                rows: null
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
                    this.fetchData()
                } else if (!newScatterAccount) {
                    this.rows = []
                }
            }
        },


        methods: {
            fetchData () {
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
                    limit: -1
                }).then(({rows}) => {
                    console.log(rows)
                    this.rows = rows.filter(row => row.owner === this.scatterAccount.name || row.backups.includes(this.scatterAccount.name))
                })
            }
        },

        beforeRouteEnter (to, from, next) {
            next(vm => {
                if (vm.scatterAccount && vm.scatterAccount.name) {
                    vm.fetchData()
                }
            })
        }
    }
</script>

<style>

</style>
