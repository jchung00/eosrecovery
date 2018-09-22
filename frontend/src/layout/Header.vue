<template>
  <!--Nav Bar-->
  <b-navbar toggleable="md" type="light" fixed="top">

    <!--Brand Logo-->
    <b-navbar-brand to="/">
      Home
    </b-navbar-brand>

    <b-navbar-toggle target="nav_collapse"></b-navbar-toggle>

    <b-collapse is-nav id="nav_collapse">
      <!-- Left elements -->
      <b-navbar-nav>
        <b-nav-item to="partners" class="mx-1">Recovery Partners</b-nav-item>
        <b-nav-item to="recover" class="mx-1">Recover</b-nav-item>
      </b-navbar-nav>

      <!-- Right elements -->
      <b-navbar-nav class="ml-auto">

        <b-nav-item right v-if="!scatter" class="mx-2">
          Download Scatter
        </b-nav-item>
        <b-nav-item right v-if="scatter && !identity" @click="linkIdentity" class="mx-2">
          Link Scatter
        </b-nav-item>

        <b-nav-item-dropdown right v-if="scatter && identity" id="last-item" class="mx-2">
          <!-- Using button-content slot -->
          <template slot="button-content">
            <em> {{ scatterAccount.name }} </em>
          </template>
          <b-dropdown-item href="#" @click="changeIdentity">Change Identity </b-dropdown-item>
          <b-dropdown-item href="#" @click="removeIdentity">Signout</b-dropdown-item>
        </b-nav-item-dropdown>
      </b-navbar-nav>
    </b-collapse>

  </b-navbar>
</template>

<script>
import { mapState, mapActions, mapGetters } from 'vuex'

export default {
  name: 'Header',
  components: {

  },
  data () {
      return {
      }
  },
  computed: {
    ...mapState({
      scatter: state => state.scatter.scatter
    }),
    ...mapGetters({
      identity: 'scatter/scatterIdentity',
      scatterAccount: 'scatter/scatterAccount'
    })
  },
  methods: {
    ...mapActions({
      linkIdentity: 'scatter/LINK_IDENTITY',
      changeIdentity: 'scatter/CHANGE_IDENTITY',
      removeIdentity: 'scatter/REMOVE_IDENTITY'
    })
  },
}
</script>

<style>
.navbar {
  height: 60px;
  background: white;
}

#nav-logo {
  position: relative;
  z-index: 6;
}

#nav_collapse {
  background: white;
  width: 100%;
}

#nav a {
  font-weight: bold;
  color: #2c3e50;
}

#nav a.router-link-exact-active {
  color: #42b983;
}

</style>
