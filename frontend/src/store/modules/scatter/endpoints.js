const mainnet = {
    id: 'eosrioapi',
    account: 'eosriobrazil',
    description: 'EOS Rio',
    chain: 'mainnet',
    supports: ['default', 'producers'],
    blockchain: 'eos',
    chainId: 'aca376f206b8fc25a6ed44dbdc66547c36c6c33e3a119ffbeaef943642f0e906',
    port: 443,
    protocol: 'https',
    host: 'api.eosrio.io',
    httpEndpoint: 'https://api.eosrio.io'
  }
  
  const local = {
    chain: 'local',
    blockchain: 'eos',
    chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f',
    port: 8888,
    protocol: 'http',
    host: 'wps-test.hkeos.com',
    httpEndpoint: 'http://wps-test.hkeos.com:8888'
  }
  
  const jungle = {
    id: 'alohajungle',
    account: 'alohaeosprod',
    description: 'Aloha EOS',
    chain: 'jungle',
    supports: ['default', 'actions', 'producers'],
    blockchain: 'eos',
    chainId: '038f4b0fc8ff18a4f0842a8f0564611f6e96e8535901dd45e43ac8691a1c4dca',
    port: 443,
    protocol: 'https',
    host: 'api.jungle.alohaeos.com',
    httpEndpoint: 'https://api.jungle.alohaeos.com'
  }
  
  export {
    mainnet,
    jungle,
    local
  }
  