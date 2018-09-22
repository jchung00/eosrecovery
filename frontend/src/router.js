import Vue from 'vue'
import Router from 'vue-router'

// Pages
import Home from './pages/Home.vue'
import Recovery from './pages/Recovery.vue'

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
      path: '/recovery',
      name: 'Recovery',
      component: Recovery
    }
  ]
})
