'use strict';

const  SEnum = require('libs/enum'),
    mongo = require('models/mongo'),
    jwt = require('jsonwebtoken');

require('sinon-mongoose');
require('chai').should();

const notify = require('libs/batch/notification').notify;
const Recovery = mongo.Recovery;
const Notification = mongo.Notification;


module.exports = exports = function() {
    const recoverer = [{
        account : 'useraaaaaaaa',
        cell : '821049087976'
    }, {
        account : 'useraaaaaaab',
        cell : '821049087976'
    }, {
        account : 'useraaaaaaac',
        cell : '821049087976'
    }];

    const cellHash = jwt.sign(JSON.stringify(recoverer), 'useraaaaaaaa');

    describe('notification', () => {
        before(async function() {
            console.log('1');
            await Recovery.create({account : 'useraaaaaaaa', cell_hash : cellHash});
            console.log('2');
            await Notification.create({account : 'useraaaaaaaa', cell_hash : cellHash, type : SEnum.NOTI_TYPE_SET});
            await Notification.create({account : 'useraaaaaaaa', recoverer : 'useraaaaaaab', type : SEnum.NOTI_TYPE_RECOVER, agree : true });
            await Notification.create({account : 'useraaaaaaaa', recoverer : 'useraaaaaaac', type : SEnum.NOTI_TYPE_RECOVER, agree : false});
        });

        after(async function() {
            await Recovery.remove({});
            await Notification.remove({});
        });

        it('notify', async function() {
            console.log('notify');
            return notify();
        });
    });
};

