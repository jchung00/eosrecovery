'use strict';

module.exports = exports = function(mongoose, conn) {
    const Schema = mongoose.Schema,
        notificationSchema = new Schema({
            account : {type : String, index : true},
            type : {type : Number},
            recoverer : {type : String},
            agree : {type : Boolean, default : false},
            processed : {type : Boolean, default : false},
            created_at : {type : Date, default : Date.now}
        });

    return conn.model('Notification', notificationSchema);
};
