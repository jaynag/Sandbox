//
//  main.cpp
//  Test
//
//  Created by Jayashree Nagarajan on 8/10/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

#include "KeyHandler.hpp"
#include "curl/curl.h"

bool isRegistered = false;

    std::size_t callback(
                         const char* in,
                         size_t size,
                         size_t num,
                         string* out)
    {
        const std::size_t totalBytes(size * num);
        //out->append(in, totalBytes);
        cout << "\n Callback executed\n";
        cout << in;
        isRegistered = true;
        return totalBytes;
    }


int MakeConnection(KeyHandler *key_handler)
{
    //string url_string = "http://google.com";
    string url_string = "https://sandboxapi.whare.cloud/api/v0.1/";
    string _authorizationHeaderName = "Authorization";
    string _appInstanceEndpoint = "app/instance/";
    string _virtualSpaceEndpoint = url_string + "ar/virtualspace/";
    string nonce = key_handler->GenerateNonce();
    
    string client_info_field = "user_id: ";
    string client_header = client_info_field + key_handler->GenerateUserId();
    string client_guid_header = "client_id";
    string client_guid = "f4e76a05-453b-4ebc-95db-7e107f9a991c";

    string signature = key_handler->GenerateSignature(nonce);
    string authHeader = "Token " + key_handler->GetLicenceKey() + " " + signature + " " + nonce;
    
    cout << "SIGNATURE: " << signature;
    
    string auth_header = _authorizationHeaderName + ": " + authHeader;// + client_guid_header + ": " + client_guid;
    string app_instance_header = url_string + _appInstanceEndpoint;
    string guid_header = client_guid_header + ": " + client_guid;
    
    cout << endl << "AUTH HEADER: " << auth_header << endl;
    cout << endl << "APP INSTANCE HEADER: " << app_instance_header << endl;
    
    struct curl_slist *headers = NULL;
    
    const string url(url_string);
    
    CURL* curl = NULL;
    
    
    //headers = curl_slist_append(headers, "charsets: utf-8");
    //headers = curl_slist_append(headers, (const char *)app_instance_header.c_str());
    //headers = curl_slist_append(headers, (const char *)auth_header.c_str());
    //headers = curl_slist_append(headers, (const char *)guid_header.c_str());
    //curl_easy_setopt(curl, CURLOPT_HTTPGET, guid_header.c_str());
    //curl_easy_setopt(curl, CURLOPT_HTTPGET, auth_header.c_str());
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, guid_header.c_str());
    //curl_easy_cleanup(curl);
    /*
     Auth Header : Token 1B3AF349123A4450A72D1C0F87A83B96 3cTCQTwYKk58/fNuukhGeQ== dxtotgjqoxjfjoshvtzz
     Auth Header:  Token 1B3AF349123A4450A72D1C0F87A83B96 a5uUkeXAkjF/dEpSSDcExiE= tvjejotrbjdlhehwfgqv
     
     */
    
    curl = curl_easy_init();
    
    if(curl)
    {
        
        int httpCode(0);
        std::unique_ptr<std::string> httpData(new std::string());
        
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        //Set remote URL
        curl_easy_setopt(curl, CURLOPT_URL, _virtualSpaceEndpoint.c_str());
        //headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, (const char *)auth_header.c_str());
        headers = curl_slist_append(headers, (const char *)guid_header.c_str());
        
        CURLcode res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
        
        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        
        cout << endl << "HTTP Code: " << httpCode << endl;
        if(res != CURLE_OK)
        {
            cout << "Curl Response failed";
        }
        else{
            cout << endl << "Success" << endl;
        }
        if(CURLE_OK == res) {
            char *ct;
            /* ask for the content-type */
            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
            if((CURLE_OK == res) && ct)
                //printf("We received Content-Type: %s\n", ct);
                printf("We received Content-Type: \n");
        }
    }
    return 0;
    
}



int main(int argc, const char * argv[]) {
    
    string app_key = "1B3AF349123A4450A72D1C0F87A83B96";
    //string app_key = "";
    string secret = "r-pNbcsZdlDV2yCUK7D4j-_IopRCi0dAAsLLkHu2WXA=";
    //string secret = "something";
    string userid = "Test User-";
    
    WhareConfiguration config = {
        .app_key = app_key,
        .secret = secret,
        .user_id = userid,
        .use_multicast = true
    };

    
    KeyHandler * key_handler = new KeyHandler(config);
    int code = MakeConnection(key_handler);
    cout << endl << "Http Code :" << code;
    return 0;
}

