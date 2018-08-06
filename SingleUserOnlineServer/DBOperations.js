
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
   var sql = "SELECT * FROM singleuser.user_info\n" +
       "WHERE user_name = '"+userName+"';"
    connection.query(sql, function (err, result) {
        if(err){
            callback("");
        } else {
            if(result.length > 0) {
                console.log(result[0]);
                callback(result[0].user_pwd.toString());
            } else {
                callback("");
            }
        }
    })
}

//创建一个新的用户
function createNewUser(userName, pwd, callback){
    var sql = "insert into  singleuser.user_info \n" +
        "(user_name, user_pwd)\n" +
        "values\n" +
        "('"+userName+"','"+pwd+"');"
    console.log("createNewUser sql = " + sql);
    connection.query(sql, function (err, result) {
        if(err){
            callback(-1);
        } else {
            callback(0);
        }
    })
}

function loadRules(callback){
    var sql = "select * from user_forbid;"
    connection.query(sql, function (err, result) {
        if(err) {
            callback([]);
        } else {
            var array = new Array();
            result.forEach(function (rule, index, a){
                array.push(rule.useridrexp);
            });

            callback(array);
        }
    })
}


exports.createTables = createTables;
exports.createNewUser = createNewUser;
exports.queryPwd = queryPwd;
exports.loadRules = loadRules;