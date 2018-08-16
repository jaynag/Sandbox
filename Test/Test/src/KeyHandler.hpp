//
//  KeyHandler.hpp
//  Whare_Unity_MacOS
//
//  Created by Jayashree Nagarajan on 8/10/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

#ifndef KeyHandler_hpp
#define KeyHandler_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "openssl/hmac.h"
#include "openssl/md5.h"
#include "openssl/bio.h"
#include "openssl/buffer.h"
#include "openssl/evp.h"
#include "openssl/sha.h"

#endif /* KeyHandler_hpp */

using namespace std;

struct WhareConfiguration
{
    string app_key;
    string secret;
    string user_id;
    bool use_multicast;
};

class KeyHandler
{
private:
    const int NONCE_SIZE = 20;
    WhareConfiguration config;
    
public:
    KeyHandler(WhareConfiguration config);
    ~KeyHandler();
    
    string GetLicenceKey();
    string GenerateNonce();
    string GenerateSignature(string nonce);
    string GenerateUserId();
    string CreateToken(string message, string secret);
};
