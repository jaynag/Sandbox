//
//  main.cpp
//  Test
//
//  Created by Jayashree Nagarajan on 8/10/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

//#include "KeyHandler.hpp"
//#include "curl/curl.h"
//#include <future>
#include <json/json.hpp>
#include "WhareAPI.hpp"

bool isRegistered = false;
string client_id = "";

    std::size_t clientIdRecieved(
                         const char* in,
                         size_t size,
                         size_t num,
                         string* out)
    {
        const std::size_t totalBytes(size * num);
        cout << "NUM " << num << " SIZE " << size;
        //out->append(in, totalBytes);
        cout << "\n Callback executed" ;
        cout << endl << in << endl;
        string client_id_str = in;
        client_id = client_id_str.substr(16,36);
        cout << "CLIENT ID " << client_id << endl;
        
        isRegistered = true;
        return totalBytes;
    }

std::size_t callback(
                             const char* in,
                             size_t size,
                             size_t num,
                             string* out)
{
    const std::size_t totalBytes(size * num);
    //out->append(in, totalBytes);
    cout << "\n Callback executed" ;
    cout << endl << in << endl;
    return totalBytes;
}

//int MakeConnection(KeyHandler *key_handler, string client_id)
//{
//    string url_string = "https://sandboxapi.whare.cloud/api/v0.1/";
//    
//    //string _appInstanceEndpoint = "app/instance/";
//    string _virtualSpaceEndpoint = url_string + "ar/virtualspace/";
//    string nonce = key_handler->GenerateNonce();
//    
//    string authorization_name = "Authorization";
//    string authorization_value = "Token " + key_handler->GetLicenceKey() + " " + key_handler->GenerateSignature(nonce) + " " + nonce;
//    string authorization_header = authorization_name + ": " + authorization_value;
//    
//    string client_id_name = "client_id";
//    string client_id_value = client_id;//"f4e76a05-453b-4ebc-95db-7e107f9a991c";
//    string client_id_header = client_id_name + ": " + client_id_value;
//    
//    struct curl_slist *headers = NULL;
//    
//    //const string url(url_string);
//    
//    CURL* curl = NULL;
//    curl = curl_easy_init();
//    int httpCode(0);
//    
//    if(curl)
//    {
//        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
//        
//        //Set remote URL
//        curl_easy_setopt(curl, CURLOPT_URL, _virtualSpaceEndpoint.c_str());
//        
//        headers = curl_slist_append(headers, (const char *)authorization_header.c_str());
//        headers = curl_slist_append(headers, (const char *)client_id_header.c_str());
//        
//        CURLcode res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
//        
//        res = curl_easy_perform(curl);
//        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
//        
////        if(res != CURLE_OK)
////        {
////            cout << "Curl Response failed";
////        }
////        else{
////            cout << endl << "Success" << endl;
////        }
////        if(CURLE_OK == res) {
////            char *ct;
////            /* ask for the content-type */
////            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
////            if((CURLE_OK == res) && ct)
////                //printf("We received Content-Type: %s\n", ct);
////                printf("We received Content-Type: \n");
////        }
//    }
//    return httpCode;
//    
//}
//
//struct client_info
//{
//    string guid;
//    int result;
//};

//client_info get_client_info(KeyHandler *key_handler)
//{
//    string url_string = "https://sandboxapi.whare.cloud/api/v0.1/";
//
//    string _appInstanceEndpoint = url_string + "app/instance/";
//    string nonce = key_handler->GenerateNonce();
//
//    string authorization_name = "Authorization";
//    string authorization_value = "Token " + key_handler->GetLicenceKey() + " " + key_handler->GenerateSignature(nonce) + " " + nonce;
//    string authorization_header = authorization_name + ": " + authorization_value;
//
//    struct curl_slist *headers = NULL;
//
//    CURL* curl = NULL;
//    curl = curl_easy_init();
//    int httpCode(0);
//
//    if(curl)
//    {
//        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
//
//        //Set remote URL
//        curl_easy_setopt(curl, CURLOPT_URL, _appInstanceEndpoint.c_str());
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "user_id: jayashree");
//        headers = curl_slist_append(headers, (const char *)authorization_header.c_str());
//
//        CURLcode res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, clientIdRecieved);
//
//        res = curl_easy_perform(curl);
//        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
//    }
//
//    client_info c_info = {
//        .guid = client_id,
//        .result = httpCode
//    };
//
//    return c_info;
//}

bool is_prime(int x)
{
    cout << "Calculating. Please, wait ...\n";
    for (int i = 2; i < x; i++)
    {
        if(x % i == 0)
            return false;
    }
    return true;
}


int main(int argc, const char * argv[]) {
    
//    future<bool> fut = async(is_prime , 313222313);
//
//    cout << "Checking whether 313222313 is prime. \n";
//
//    bool ret = fut.get();
//    if(ret) cout << "It is prime!\n";
//    else cout << "It is not prime :(\n";
    
    
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
    
//    future<client_info> fut = async(get_client_info, key_handler);
//    client_info c_info = fut.get();
//    cout << "HTTP CODE " << c_info.result << endl;
//    if(isRegistered)
//    {
//        int code = MakeConnection(key_handler, c_info.guid);
//        cout << endl << "Http Code :" << code;
//    }

    WhareAPI *api = new WhareAPI();
    api->RegisterApp(key_handler);
}


/*
 headers = curl_slist_append(headers, "charsets: utf-8");
 headers = curl_slist_append(headers, (const char *)app_instance_header.c_str());
 headers = curl_slist_append(headers, (const char *)auth_header.c_str());
 headers = curl_slist_append(headers, (const char *)guid_header.c_str());
 curl_easy_setopt(curl, CURLOPT_HTTPGET, guid_header.c_str());
 curl_easy_setopt(curl, CURLOPT_HTTPGET, auth_header.c_str());
 curl_easy_setopt(curl, CURLOPT_POSTFIELDS, guid_header.c_str());
 curl_easy_cleanup(curl);
 //headers = curl_slist_append(headers, "Content-Type: application/json");
 Auth Header : Token 1B3AF349123A4450A72D1C0F87A83B96 3cTCQTwYKk58/fNuukhGeQ== dxtotgjqoxjfjoshvtzz
 Auth Header:  Token 1B3AF349123A4450A72D1C0F87A83B96 a5uUkeXAkjF/dEpSSDcExiE= tvjejotrbjdlhehwfgqv
 //std::unique_ptr<std::string> httpData(new std::string());
 //curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
 
 */
