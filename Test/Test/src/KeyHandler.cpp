//
//  KeyHandler.cpp
//  Whare_Unity_MacOS
//
//  Created by Jayashree Nagarajan on 8/10/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

#include "KeyHandler.hpp"
#include <cstdlib>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <random>

using namespace std;



char *base64(const unsigned char *input, int length)
{
    BIO *bmem, *b64;
    BUF_MEM *bptr;
    
    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    
    char *buff = (char *)malloc(bptr->length);
    memcpy(buff, bptr->data, bptr->length-1);
    buff[bptr->length-1] = 0;
    
    BIO_free_all(b64);
    
    return buff;
}

char *decode64(unsigned char *input, int length)
{
    BIO *b64, *bmem;
    
    char *buffer = (char *)malloc(length);
    memset(buffer, 0, length);
    
    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    
    BIO_read(bmem, buffer, length);
    
    BIO_free_all(bmem);
    
    return buffer;
}


KeyHandler::KeyHandler(WhareConfiguration _config)
{
    config = _config;
}

KeyHandler::~KeyHandler()
{
    
}

string KeyHandler::GetLicenceKey()
{
    return config.app_key;
}

string KeyHandler::GenerateNonce()
{
    string nonce = "";
    float max = 122.999, min = 97;

    for (int i = 0; i < NONCE_SIZE; ++i)
    {
        random_device rd;
        mt19937 mt(rd());
        uniform_real_distribution<float> dist(min, max);
        
        float random = dist(mt);
        nonce += (char)random;
    }
    return nonce;
}

string KeyHandler::GenerateUserId()
{
    int x = rand() % 10 + 1;
    string userId = config.user_id + to_string(x);
    //string hashId = base64_encode(CreateToken("", userId));
    //string token = CreateToken("", userId);
    //char * hashId = base64(token, 16);
    //return hashId;
    return userId;
}

string KeyHandler::GenerateSignature(string nonce)
{
    string payload = config.app_key + nonce;
    return CreateToken(payload, config.secret);
}

string KeyHandler::CreateToken(string message, string secret)
{
    char keyChar[secret.length()];
    char messageChar[message.length()];
    
    strcpy(keyChar, secret.c_str());
    strcpy(messageChar, message.c_str());
    
    unsigned char* result;
    unsigned int len = 16;
    
    result = (unsigned char*)malloc(sizeof(char) * len);
    
    HMAC_CTX ctx;
    HMAC_CTX_init(&ctx);

    HMAC_Init_ex(&ctx, keyChar, strlen(keyChar), EVP_md5(), NULL);
    HMAC_Update(&ctx, (unsigned char*)&messageChar, strlen(messageChar));
    HMAC_Final(&ctx, result, &len);
    HMAC_CTX_cleanup(&ctx);
    
    free(result);
    return base64(result, len);
}


