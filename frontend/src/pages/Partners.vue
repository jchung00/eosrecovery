<template>
    <main role="main">
        <div class="jumbotron jumbotron-fluid mb-3 py-5">
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
        <div class="container">
            <div class="table-responsive">

                <table class="table">
                    <thead class="thead" id="custom-head">
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
                                          class="mb-2"
                                          @click="deletePartner(index)"
                                          v-else
                                          id="custom-button">
                                    Delete Partner
                                </b-button>
                            </td>
                        </tr>

                        <tr>
                            <td>{{ rows.length + 1 }}</td>
                            <td class="text-center">
                                <b-form-input v-model="newUsername"
                                              type="text"
                                              placeholder="Enter Username"
                                              required
                                              id="custom-input"
                                >
                                </b-form-input>

                            </td>
                            <td>
                                <b-button
                                        variant="secondary"
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
export default {
  name: 'Partners',

  data () {
    return {
        newUsername: null,
        rows: [{
            username: 'hkeoshkeosbp',
        }]
    }
  },

  methods: {
      addPartner () {
          if (this.newUsername) {
            this.rows.push({
                username: this.newUsername,
            })
            this.newUsername = null
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

    #custom-button {
        border-radius: 25px;
    }

    #custom-input {
        width: 50%;
        margin-left: auto;
        margin-right: auto;
    }

</style>
