//
//  CommonTools.cpp
//  SingleUserOnlineSvrCPP
//
//  Created by castlebai on 9/8/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#include "CommTools.hpp"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/md5.h>
#include "../GlobalData.hpp"

string CommTools::RsaDecode(const string strData){
    std::string strRet;
    BIO* bio = NULL;
    RSA* pRsaPrivateKey = NULL;
    if((bio = BIO_new_mem_buf((void*)GlobalData::PRIVATE_KEY.c_str(), -1)) == NULL){
        return "";
    }
    pRsaPrivateKey = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
    char* content = new char[strData.length()];
    int result = RSA_private_decrypt(strData.length()+1, (const unsigned char*)strData.c_str(),
                                     (unsigned char*)content, pRsaPrivateKey, RSA_PKCS1_OAEP_PADDING);
    if(ret >= 0) {
        strRet = buff_to_hexstring(<#const char *szBuff#>, <#int nSize#>)
    }
    BIO_free_all(bio);
  
    return strRet;
}

string CommTools::RsaEncodeWithSvr(const string strData){
    std::string strRet;
    BIO* bio = NULL;
    RSA* pRSAPublicKey = NULL;
    if((bio = BIO_new_mem_buf((void*)GlobalData::PUBLIC_KEY.c_str(), -1)) == NULL){
        return "";
    }
    pRSAPublicKey = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free_all(bio);
    
    int nLen = RSA_size(pRSAPublicKey);
    char* pDecode = new char[nLen/2 + 2];
    char* pEncode = new char[nLen/2 + 2];
    hexstring_to_buff(strData, pEncode, nLen);
    int ret = RSA_public_encrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pDecode, pRSAPublicKey, RSA_PKCS1_OAEP_PADDING);
    if (ret >= 0)
    {
        strRet = string(pDecode);
    }
    delete[] pEncode;
    delete[] pDecode;
    RSA_free(pRSAPublicKey);
    CRYPTO_cleanup_all_ex_data();
    return strRet;
}

std::string CommTools::buff_to_hexstring(const char *szBuff, int nSize)
{
    std::string strHex;
    size_t nPos = 0;
    while (nPos < nSize)
    {
        strHex += CharBase[((szBuff[nPos]) >> 4) & 0xF];
        strHex += CharBase[szBuff[nPos] & 0xF];
        nPos++;
    }
    return strHex;
}

int CommTools::hexstring_to_buff(const std::string strHexString, char *szBuff, int nSize)
{
    const char * pHexStr = strHexString.c_str();
    size_t nHexLen = strHexString.length();
    if (nHexLen % 2) nHexLen--;
    size_t nPos = 0;
    size_t nOutPos = 0;
    while (nPos < nHexLen && nOutPos < nSize)
    {
        szBuff[nOutPos++] = (GetCharVal(pHexStr[nPos]) << 4 & 0xF0) | (GetCharVal(pHexStr[nPos + 1]) & 0xF);
        nPos += 2;
    }
    return static_cast<int>(nOutPos);
}

char CommTools::GetCharVal(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 0x0A;
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 0x0A;
    }
    else
    {
        return 0;
    }
}

string CommTools::getMD5(const string& src)
{
    MD5_CTX ctx;
    
    string md5_string;
    unsigned char md[16] = { 0 };
    char tmp[33] = { 0 };
    
    MD5_Init( &ctx );
    MD5_Update( &ctx, src.c_str(), src.size() );
    MD5_Final( md, &ctx );
    
    for( int i = 0; i < 16; ++i )
    {
        memset( tmp, 0x00, sizeof( tmp ) );
        sprintf( tmp, "%02X", md[i] );
        md5_string += tmp;
    }
    return md5_string;
}
