
var Rsa = require("node-rsa")

// 用私钥解密
function RsaDecode(content){


    var priKey = new Rsa(global.private_key);
    var buff = Buffer.from(content, "hex");
    var decrypted = priKey.decrypt(buff);
    console.log(decrypted.toString());
    return decrypted.toString();
}

exports.RsaDecode = RsaDecode