'use strict';

const _ = require('lodash'),
    Eos = require('eosjs'),
    config = require('config');

const {format /*, api, ecc, json, Fcbuffer*/} = Eos.modules;

const eosNodeConfig = config.eosNode;
const recoveryAccount = eosNodeConfig.recoveryAccount;

function getConfig(key, httpEndPoint) {
    const endpoint = getEndpoint(httpEndPoint);
    return {
        keyProvider: key, // || eosNodeConfig.watchmanPriKey,
        httpEndpoint: endpoint,
        // mockTransactions: () => 'pass', // or 'fail'
        // transactionHeaders: (expireInSeconds, callback) => { callback(null/*error*/, headers)},
        expireInSeconds: 60,
        broadcast: true,
        debug: false,
        sign: true,
        chainId: eosNodeConfig.chainId,
        verbose: false,
        logger: {
            log: false ? console.log : null,  // null to disable
            error: false ? console.error : null,
        }
    };
}

function getEndpoint(endpoint) {
    if (_.isEmpty(endpoint)) {
        endpoint = `${eosNodeConfig.protocol}://${eosNodeConfig.host}:${eosNodeConfig.httpPort}`;
    }
    return endpoint;
}

function getInfo(endpoint) {
    const options = getConfig(endpoint);
    const eos = Eos(options);
    return eos.getInfo({})
        .catch(function(err) {
            if (typeof err === 'string') {
                throw JSON.parse(err);
            }
            throw err;
        });
}

function getBlock(blockId, endpoint) {
    const options = getConfig(endpoint);
    const eos = Eos(options);
    return eos.getBlock(blockId)
        .catch(function(err) {
            if (typeof err === 'string') {
                throw JSON.parse(err);
            }
            throw err;
        });
}

function getTableRows(code, scope, table, tableKey, lowerBound, limit, keyType, indexPosition, endpoint) {
    const options = getConfig(endpoint);
    const eos = Eos(options);

    const params = {
        json : true, // {type : "bool", "default": false},
        code : code,
        scope : scope,
        table : table,
        table_key : tableKey,
        lower_bound : lowerBound,
        //upper_bound: {type : "string", default: '-1'},
        limit : limit,
        key_type : keyType,
        index_position : indexPosition
    };

    return eos.getTableRows(params)
        .catch(function(err) {
            if (typeof err === 'string') {
                throw JSON.parse(err);
            }
            throw err;
        });
}

function getVoterInfo(voter) {
    // console.log(format.encodeName(voter, false));
    const systemAccount = eosNodeConfig.systemAccount;
    return getTableRows(systemAccount, systemAccount, 'voters', null, format.encodeName(voter, false), 1, 'i64', 1)
        .then(function(result) {
            if (!_.isEmpty(result.rows)) {
                return result.rows[0];
            }
            return {};
        });
}

function getProposalById(proposalId) {
    return getTableRows(recoveryAccount, recoveryAccount, 'proposals', null, proposalId, 1, 'i64', 2)
        .then(function(result) {
            if (!_.isEmpty(result.rows)) {
                return result.rows[0];
            }
            return {};
        });
}

function getCurrencyStats(endpoint) {
    const tokenAccount = eosNodeConfig.tokenAccount;
    const options = getConfig(endpoint);
    const eos = Eos(options);
    return eos.getCurrencyStats(tokenAccount, 'EOS');
}

function getEos(endpoint) {
    const options = getConfig(endpoint);
    return Eos(options);
}

module.exports = exports = {getInfo, getBlock, getTableRows,
    getVoterInfo, getProposalById, getCurrencyStats,
    getEos,
};


