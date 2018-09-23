'use strict';

require('chai').should();
const eosApi = require('external_apis/eos_api'),
    smsApi = require('external_apis/sms_api');

describe('[external_apis]', function() {

    it('sendSms', async function() {
        return smsApi.sendSMS('+821049087976', 'testmsg2')
        .then(function(result) {
            console.log(result);
        });
    });

    it('getInfo', async function() {
        return eosApi.getInfo()
        .then(function(result) {
            console.log(result);
        });
    });

    it('getBlock', async function() {
        return eosApi.getBlock(10)
        .then(function(result) {
            console.log(result);
        });
    });

    it.skip('getProposalById', async function() {
        return eosApi.getProposalById(1)
        .then(function(result) {
            console.log(result);
        });
    });

    it.skip('getProposalByOwner', async function() {
        return eosApi.getProposalByOwner('proposeraaaa')
        .then(function(result) {
            console.log(result);
        });
    });

    it('getCurrencyStats', async function() {
        return eosApi.getCurrencyStats()
        .then(function(result) {
            console.log(result);
        });
    });

});

