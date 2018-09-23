<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid py-5">
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

        <div class="container">
            <div class="table-responsive">

                <table class="table">
                    <thead>
                    <tr>
                        <th scope="col">#</th>
                        <th scope="col">Username</th>
                        <th scope="col">Permission</th>
                        <th scope="col">Actions</th>
                    </tr>
                    </thead>

                    <tbody>
                    <tr v-for="(row, index) in rows" :key="index">
                        <td class="align-middle">{{ index + 1 }}</td>
                        <td class="align-middle">{{ row.username }}</td>
                        <td class="align-middle">{{ row.permission }} </td>
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

        methods: {
            addPartner () {
                if (this.newUsername && this.newPermission) {
                    this.rows.push({
                        username: this.newUsername,
                        permission: this.newPermission
                    })

                    this.newUsername = null
                    this.newPermission = null
                }
            },

            deletePartner (index) {
                this.rows.splice(index, 1)
            },

            savePartners () {

            }
        }
    }
</script>

<style>

</style>
