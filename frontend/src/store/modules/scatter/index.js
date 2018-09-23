import ScatterJS from 'scatter-js/dist/scatter.esm';
import { jungle } from './endpoints'

const network = jungle

export default {
  namespaced: true,

  state: {
    scatter: null
  },

  actions: {
    async CONNECT_SCATTER ({ commit }) {
      ScatterJS.scatter.connect('recovery-app').then(connected => {
        if (connected) {
          commit('SET_SCATTER', ScatterJS.scatter)
          window.scatter = null
        }
      })
    },

    async SET_SCATTER ({ commit }, scatter) {
      commit('SET_SCATTER', scatter)
    },

    async LINK_IDENTITY ({ state }) {
      if (state.scatter) {
        state.scatter.getIdentity({accounts: [ network ]})
      }
    },

    async CHANGE_IDENTITY ({ dispatch, state }) {
      if (state.scatter) {
        state.scatter.forgetIdentity().then(() => {
          dispatch('LINK_IDENTITY', true)
        })
      }
    },

    async REMOVE_IDENTITY ({ state }) {
      if (state.scatter) {
        state.scatter.forgetIdentity()
      }
    }
  },

  mutations: {
    SET_SCATTER (state, scatter) {
      state.scatter = scatter
    }
  },

  getters: {
    scatterAccount: (state) => {
      return state.scatter && state.scatter.identity
              ? state.scatter.identity.accounts[0]
              : null
    },
    scatterIdentity: (state) => {
      return state.scatter
              ? state.scatter.identity
              : null
    }
  }
}
