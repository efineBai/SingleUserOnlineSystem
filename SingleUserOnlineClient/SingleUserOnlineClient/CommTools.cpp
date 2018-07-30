//
//  CommTools.cpp
//  SingleUserOnlineClient
//
//  Created by castlebai on 29/7/2018.
//  Copyright © 2018 castlebai. All rights reserved.
//

#include "CommTools.hpp"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "GlobalData.hpp"

string CommTools::RsaEncodeWithSvr(const string strData){
    std::string strRet;
    BIO* bio = NULL;
    RSA* pRSAPublicKey = NULL;
    if((bio = BIO_new_mem_buf((void*)GlobalData::PUBLIC_KEY.c_str(), -1))){
        return "";
    }
    pRSAPublicKey = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free_all(bio);
    
    int nLen = RSA_size(pRSAPublicKey);
    char* pEncode = new char[nLen + 1];
    int ret = RSA_public_encrypt(strData.length(), (const unsigned char*)strData.c_str(), (unsigned char*)pEncode, pRSAPublicKey, RSA_PKCS1_PADDING);
    if (ret >= 0)
    {
        strRet = std::string(pEncode, ret);
    }
    delete[] pEncode;
    RSA_free(pRSAPublicKey);
    CRYPTO_cleanup_all_ex_data();
    return strRet;
}
