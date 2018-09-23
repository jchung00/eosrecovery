'use strict';

const _ = require('lodash'),
    mongo = require('models/mongo'),
    SEnum = require('libs/enum');

const Recovery = mongo.Recovery;
const Notification = mongo.Notification;

async function setrecovery(action) {
    let data = Object.assign({}, {account : action.data.owner}, {cell_hash : action.data.cell_hash});
    await Recovery.update({account : action.data.owner}, data, {upsert : true});
    await Notification.create({account : action.data.owner, type : SEnum.NOTI_TYPE_SET});
}

async function chgrecovery(action) {
    // let data = Object.assign({}, action.data, {account : action.data.ower});
    // await Notification.create({account : action.data.owner, type : SEnum.NOTI_TYPE_SET});
}

async function recover(action) {
    await Notification.create({account : action.data.owner, recoverer : action.data.recoverer, type : SEnum.NOTI_TYPE_RECOVER, agree : action.data.agree});
}

module.exports = exports = {setrecovery, chgrecovery, recover};
