//
//  CommTools.hpp
//  SingleUserOnlineClient
//
//  Created by castlebai on 29/7/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#ifndef CommTools_hpp
#define CommTools_hpp

#include <stdio.h>
#include <string>


using std::string;
namespace CommTools {
    const static char CharBase[] = { '0','1','2','3',
        '4','5','6','7',
        '8','9','A','B',
        'C','D','E','F' };
    static    char GetCharVal(char c);
    string RsaEncodeWithSvr(const string);
    static string buff_to_hexstring(const char *szBuff, int nSize);
    static int hexstring_to_buff(const std::string strHexString, char *szBuff, int nSize);
    string getMD5(const string& src);
    string Sha256(const string str);
    string generateDbPwd(string pwdmd5, string salt);
}
#endif /* CommTools_hpp */
