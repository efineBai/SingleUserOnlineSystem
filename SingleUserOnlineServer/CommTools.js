
var Rsa = require("node-rsa")

// 用私钥解密
function RsaDecode(content){
    var priKey = new Rsa(global.private_key, 'pkcs8-private');
    var decrypted = priKey.decrypt(content, 'utf8');
    return decrypted;
}

exports.RsaDecode = RsaDecode