'use strict';

const Promise = require('bluebird'),
    _ = require('lodash'),
    jwt = require('jsonwebtoken'),
    smsApi = require('external_apis/sms_api'),
    mongo = require('models/mongo'),
    SEnum = require('libs/enum'),
    log = require('libs/log');

const batchErrLog = log.batchErrLog;
const batchLog = log.batchLog;

const Notification = mongo.Notification;
const Recovery = mongo.Recovery;

async function notify() {
    // batchLog.info('notify');
    const notifications = await Notification.find({processed : false}).limit(10).sort({_id : 1});
    if (!_.isEmpty(notifications)) {
        return Promise.each(notifications, function(noti) {
            if (noti.type === SEnum.NOTI_TYPE_SET) {
                return _notifySet(noti);
            } else if (noti.type === SEnum.NOTI_TYPE_RECOVER) {
                return _notifyRecover(noti);
            }
        });
    }
}

async function _notifySet(noti) {
    let recover = await Recovery.findOne({account : noti.account});
    console.log('set', noti);
    if (!_.isEmpty(recover)) {
        await smsApi.sendSMS('+' + recover.cell_hash, `Did you set up recovery for the ${noti.account} EOS account?`);
        /*
        const decoded = jwt.decode(recover.cell_hash, noti.account);
        const accounts = Array.isArray(decoded) === true ? decoded : JSON.parse(decoded);
        return Promise.map(accounts, (account) => {
            if (noti.account === account.account) {
                return smsApi.sendSMS('+' + account.cell, `Did you set up recovery for the ${noti.account} EOS account?`);
            }
        });
        */
    }
    if (!_.isEmpty(noti)) {
        console.log('remove');
        return noti.remove();
    }
}

async function _notifyRecover(noti) {
    console.log('recover', noti);
    let recover = await Recovery.findOne({account : noti.account});
    if (!_.isEmpty(recover)) {
        if (noti.agree === true) {
            await smsApi.sendSMS('+' + recover.cell_hash, `${noti.account} approves the recovery request.`);
        } else {
            await smsApi.sendSMS('+' + recover.cell_hash, `${noti.account} denied the recovery request.`);
        }
        /*
        const decoded = jwt.decode(recover.cell_hash, noti.account);
        const accounts = Array.isArray(decoded) === true ? decoded : JSON.parse(decoded);
        return Promise.map(accounts, (account) => {
            if (noti.account === account.account) {
                // return smsApi.sendSMS('+' + account.cell, 'Did you request a recovery?');
            }
            if (noti.agree === true) {
                return smsApi.sendSMS('+' + account.cell, `${noti.account} approves the recovery request.`);
            }
            return smsApi.sendSMS('+' + account.cell, `${noti.account} denied the recovery request.`);
        });
        */
    }
    if (!_.isEmpty(noti)) {
        return noti.remove();
    }
}

module.exports = exports = {notify};
