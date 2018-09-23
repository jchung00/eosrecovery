'use strict';

const config = require('config'),
    twilio = require('twilio');

const accountSid = config.twilio.accountSid; // Your Account SID from www.twilio.com/console
const authToken = config.twilio.authToken;   // Your Auth Token from www.twilio.com/console
const from = config.twilio.from;

async function sendSMS(to, msg) {
    // console.log(to, msg);
    const client = new twilio(accountSid, authToken);
    return client.messages.create({
        from: from, // From a valid Twilio number
        to: to,     // Text this number
        body: msg
    })
    .then((message) => {
        console.log(message.sid);
        return message;
    });
}

module.exports = exports = {sendSMS};


