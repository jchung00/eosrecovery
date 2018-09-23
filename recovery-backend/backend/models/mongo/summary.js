'use strict';

module.exports = exports = function(mongoose, conn) {
    const Schema = mongoose.Schema,
        schema = new Schema({
            block_id : {type : String},                         //
            block_num : {type : Number},                        //
        });
    return conn.model('Summary', schema);
};
