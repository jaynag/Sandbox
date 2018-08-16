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

/*
static const char b64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const char reverse_table[128] = {
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
};

::std::string base64_encode(const ::std::string &bindata)
{
    using ::std::string;
    using ::std::numeric_limits;
    
    if (bindata.size() > (numeric_limits<string::size_type>::max() / 4u) * 3u) {
        throw ::std::length_error("Converting too large a string to base64.");
    }
    
    const ::std::size_t binlen = bindata.size();
    // Use = signs so the end is properly padded.
    string retval((((binlen + 2) / 3) * 4), '=');
    ::std::size_t outpos = 0;
    int bits_collected = 0;
    unsigned int accumulator = 0;
    const string::const_iterator binend = bindata.end();
    
    for (string::const_iterator i = bindata.begin(); i != binend; ++i) {
        accumulator = (accumulator << 8) | (*i & 0xffu);
        bits_collected += 8;
        while (bits_collected >= 6) {
            bits_collected -= 6;
            retval[outpos++] = b64_table[(accumulator >> bits_collected) & 0x3fu];
        }
    }
    if (bits_collected > 0) { // Any trailing bits that are missing.
        assert(bits_collected < 6);
        accumulator <<= 6 - bits_collected;
        retval[outpos++] = b64_table[accumulator & 0x3fu];
    }
    assert(outpos >= (retval.size() - 2));
    assert(outpos <= retval.size());
    return retval;
}

::std::string base64_decode(const ::std::string &ascdata)
{
    using ::std::string;
    string retval;
    const string::const_iterator last = ascdata.end();
    int bits_collected = 0;
    unsigned int accumulator = 0;
    
    for (string::const_iterator i = ascdata.begin(); i != last; ++i) {
        const int c = *i;
        if (::std::isspace(c) || c == '=') {
            // Skip whitespace and padding. Be liberal in what you accept.
            continue;
        }
        if ((c > 127) || (c < 0) || (reverse_table[c] > 63)) {
            throw ::std::invalid_argument("This contains characters not legal in a base64 encoded string.");
        }
        accumulator = (accumulator << 6) | reverse_table[c];
        bits_collected += 6;
        if (bits_collected >= 8) {
            bits_collected -= 8;
            retval += static_cast<char>((accumulator >> bits_collected) & 0xffu);
        }
    }
    return retval;
}
*/

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
    
//    char mdString[16];
//
//    for (int i = 0; i < len; i++){
//        sprintf(&mdString[i*2],"%02x", (unsigned int)result[i]);
//    }
//
//    printf("\Hex String : %s\n", mdString);
    
    free(result);
    //return base64_encode((char *)result);
    return base64(result, len);
}


