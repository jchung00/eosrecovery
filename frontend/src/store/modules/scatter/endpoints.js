const mainnet = {
    blockchain: 'eos',
    chainId: 'aca376f206b8fc25a6ed44dbdc66547c36c6c33e3a119ffbeaef943642f0e906',
    port: 443,
    protocol: 'https',
    host: 'eos.greymass.com',
    httpEndpoint: 'https://eos.greymass.com'
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
    jungle
  }
  