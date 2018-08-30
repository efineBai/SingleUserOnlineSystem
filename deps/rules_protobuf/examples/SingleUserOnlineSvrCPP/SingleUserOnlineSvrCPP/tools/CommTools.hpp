//
//  CommonTools.hpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 9/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#ifndef CommonTools_hpp
#define CommonTools_hpp

#include <iostream>

using std::string;
namespace CommTools {
    const static char CharBase[] = { '0','1','2','3',
        '4','5','6','7',
        '8','9','A','B',
        'C','D','E','F' };
        char GetCharVal(char c);
    string RsaEncodePwd(const string);
    string buff_to_hexstring(const char *szBuff, int nSize);
    int hexstring_to_buff(const std::string strHexString, char *szBuff, int nSize);
    string getMD5(const string& src);
    string RsaDecode(const string);
    string Sha256(const string str);
    string generateToken();
    string generateDbPwd(string pwdmd5, string salt);
}
#endif /* CommonTools_hpp */
