import Vue from 'vue'
import Router from 'vue-router'

// Pages
import Home from './pages/Home.vue'
import Initialize from './pages/Initialize.vue'
import Partners from './pages/Partners.vue'
import Recover from './pages/Recover.vue'
import Requests from './pages/Requests.vue'

Vue.use(Router)

export default new Router({
  mode: 'history',
  routes: [
    {
      path: '/',
      name: 'home',
      component: Home
    },
    {
      path: '/initialize',
      name: 'Initialize',
      component: Initialize
    },
    {
      path: '/partners',
      name: 'Partners',
      component: Partners
    },
    {
      path: '/recover',
      name: 'Recover',
      component: Recover
    },
      {
      path: '/requests',
      name: 'Requests',
      component: Requests
    }
  ]
})
