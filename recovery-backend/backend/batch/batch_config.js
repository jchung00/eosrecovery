'use strict';

const _ = require('lodash');

module.exports = [
    {
        /*
        job_group : 'xxx_log',
        jobs : []
        */
    }, {
        job_group : 'Block',
        jobs : [
            {name : 'processActions', params : {}, schedule : {second : _.range(1, 60, 1)}, excludes : ['']},
            {name : 'notify', params : {}, schedule : {second : _.range(1, 60, 1)}, excludes : ['']},
        ]
    }
];
