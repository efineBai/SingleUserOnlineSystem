
var mysql = require("mysql");
var connection = mysql.createConnection({
    host: '127.0.0.1',
    user: 'root',
    password: 'midas5384871',
    port: '3306',
    database: 'singleuser'
})

//创建user_info 表
function createTables(callback){
    var sql = "CREATE TABLE IF NOT EXISTS `singleuser`.`user_info` (\n" +
        "  `user_name` VARCHAR(64) NOT NULL,\n" +
        "  `user_pwd` VARCHAR(64) NOT NULL,\n" +
        "  `statue` INT NULL DEFAULT 0,\n" +
        "  PRIMARY KEY (`user_name`),\n" +
        "  UNIQUE INDEX `user_name_UNIQUE` (`user_name` ASC));"

    connection.query(sql, function (err, result) {
        if(err){
            console.log("create table failed");
            callback(-1);
        } else {
            callback(0);
        }
    })
}

//查询用户的密码
function queryPwd(userName, callback){
   var sql = "SELECT user_pwd FROM singleuser.user_info\n" +
       "WHERE user_name = '"+userName+"';"
    connection.query(sql, function (err, result) {
        if(err){
            callback(-1);
        } else {
            callback(result[0].user_pwd);
        }
    })
}

//创建一个新的用户
function createNewUser(userName, pwd, callback){
    var sql = "insert into  singleuser.user_info \n" +
        "(user_name, user_pwd)\n" +
        "values\n" +
        "('"+userName+"','"+pwd+"');"
    connection.query(sql, function (err, result) {
        if(err){
            callback(-1);
        } else {
            callback(0);
        }
    })
}


exports.createTables = createTables;
exports.createNewUser = createNewUser;
exports.queryPwd = queryPwd;
