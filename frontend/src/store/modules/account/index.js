export default {
  namespaced: true,

  state: {
    accounts: null
  },

  actions: {
    async SET_USER_ACCOUNTS ({ commit }, accounts) {
      commit('SET_USER_ACCOUNTs', accounts)
    }
  },

  mutations: {
    SET_USER_ACCOUNTS (state, accounts) {
      state.scatter = accounts
    }
  }
}
