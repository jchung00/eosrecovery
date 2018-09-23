'use strict';

module.exports = exports = function(mongoose, conn) {
    const Schema = mongoose.Schema,
        schema = new Schema({
            account : {type : String, index : true, unique : true, minlength : 1, maxlength : 12},
            cell_hash : {type : String, maxlength : 1024},
        }, {timestamps : true});
    return conn.model('Recovery', schema);
};
