<template>
  <div id="app">
    <AppHeader></AppHeader>
    <b-container fluid id="main-wrapper">
      <transition name="fade">
        <router-view></router-view>
      </transition>
    </b-container>
    <AppFooter></AppFooter>
  </div>
</template>

<script>
import AppHeader from './layout/Header.vue'
import AppFooter from './layout/Footer.vue'
import { mapActions } from 'vuex'

export default {
  name: 'App',
  components: {
    AppHeader,
    AppFooter
  },
  methods: {
    ...mapActions({
      connectScatter: 'scatter/CONNECT_SCATTER'
    })
  },
  mounted () {
    this.connectScatter()
  }
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
</style>
