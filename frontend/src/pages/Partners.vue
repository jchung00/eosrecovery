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
            <h3>Current Recovery Partners</h3>

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
                        <td>{{ index + 1 }}</td>
                        <td>{{ row.username }}</td>
                        <td>{{ row.permission }} </td>
                        <td>
                            <div v-if="row.toDelete">
                                Deleted 

                                <b-button variant="danger"
                                          class="mb-2">
                                    Undo
                                </b-button>
                            </div>

                            <b-button variant="danger"
                                      class="mb-2"
                                      @click="deletePartner(index)"
                                      v-else>
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
                            <input v-model="newPermission" required/>
                        </td>
                        <td>
                            <b-button
                                variant="success"
                                class="mb-2"
                                @click="addPartner"
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
        >
            Save recovery partners
        </b-button>
    </main>
</template>

<script>
export default {
  name: 'Partners',

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
