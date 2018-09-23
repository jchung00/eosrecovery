'use strict';

const Promise = require('bluebird'),
    eosApi = require('external_apis/eos_api');

console.log(`ENV : ${process.env.NODE_ENV}`);

if (process.env.NODE_ENV === 'production') {
    console.log('NOT SUPPORT IN PRODUCTION');
    return;
}

async function updateauth() {
    const auth = {
        'account': 'yepp4youaaaa',
        'permission': 'owner',
        'parent': '',
        'auth': {
            'threshold': 1, 'keys': [], 'waits': [],
            'accounts': [{
                'weight': 1,
                'permission': {'actor': 'forgoteoskey', 'permission': 'eosio.code'}
            }]
        }
    };
    return eosApi.updateauth(auth, '5JyPYYq5yy1A4XDgeyd9MifHZGgH5xqV567Sdec7NMDZ8FGvgLw');
}

Promise.resolve(updateauth())
    .then(() => {
        console.log('complete~~');
    })
    .delay(1000);


