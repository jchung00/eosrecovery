'use strict';

const Promise = require('bluebird'),
    _ = require('lodash'),
    mongo = require('models/mongo');

console.log(`ENV : ${process.env.NODE_ENV}`);

if (process.env.NODE_ENV === 'production') {
    console.log('NOT SUPPORT IN PRODUCTION');
    return;
}

const Summary = mongo.Summary;

async function createSummary() {
    const summary = await Summary.findOne();
    if (_.isEmpty(summary)) {
        return Summary.create({block_num : 100});
    } else {
        // return Summary.updateOne({block_num : 0});
    }
}

Promise.resolve(createSummary())
    .then(() => {
        console.log('complete~~');
    })
    .delay(1000);


