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
    static    char GetCharVal(char c);
    static string RsaEncodeWithSvr(const string);
    static string buff_to_hexstring(const char *szBuff, int nSize);
    static int hexstring_to_buff(const std::string strHexString, char *szBuff, int nSize);
    static string getMD5(const string& src);
    static string RsaDecode(const string);
    
}
#endif /* CommonTools_hpp */
