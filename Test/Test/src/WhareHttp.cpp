////
////  WhareHttp.cpp
////  Whare_Unity_MacOS
////
////  Created by Jayashree Nagarajan on 8/9/18.
////  Copyright © 2018 SamsungNext. All rights reserved.
////
//
//#include "WhareHttp.hpp"
//#include "iostream"
//#include "KeyHandler.hpp"
//
//using namespace std;
//namespace
//{
//    std::size_t callback(
//                         const char* in,
//                         size_t size,
//                         size_t num,
//                         string* out)
//    {
//        const std::size_t totalBytes(size * num);
//        out->append(in, totalBytes);
//        return totalBytes;
//    }
//}
//
//WhareHttp::WhareHttp()
//{
//   // Log::debug("Http Constructor");
//}
//
//WhareHttp::WhareHttp(KeyHandler * handler)
//{
//    this->key_handler = handler;
//    // Log::debug("Http Constructor");
//}
//
//WhareHttp::~WhareHttp()
//{
//    free(key_handler);
//    //Log::debug("Http Destructor");
//}
//
//int WhareHttp::MakeConnection()
//{
//    //string url_string = "http://google.com";
//    string url_string = "https://sandboxapi.whare.cloud/api/v0.1/";
//
//    string _authorizationHeaderName = "Authorization";
//    string nonce = this->key_handler->GenerateNonce();
//    string authHeader = "Token " + key_handler->GetLicenceKey() + " " + key_handler->GenerateSignature(nonce) + " " + nonce;
//    string customHeader = _authorizationHeaderName + ": " + authHeader;
//    string client_info_field = "user_id : ";
//    string client_info = client_info_field + key_handler->GenerateUserId();
//    string client_header = url_string + ": " + client_info;
//    cout << endl << "Auth Header " << authHeader << endl;
//
//    struct curl_slist *headers = NULL;
//
//    const string url(url_string);
//
//    CURL* curl = NULL;
//
//    headers = curl_slist_append(headers, "Accept: application/json");
//    headers = curl_slist_append(headers, "Content-Type: application/json");
//    headers = curl_slist_append(headers, "charsets: utf-8");
//    headers = curl_slist_append(headers, (const char *)customHeader.c_str());
//
//    curl = curl_easy_init();
//
//    if(curl)
//    {
//        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
//        //Set remote URL
//        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//        CURLcode res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//        res = curl_easy_perform(curl);
//        if(res != CURLE_OK)
//        {
//            cout << "Curl Response failed";
//        }
//        else{
//            cout << endl << "Success" << endl;
//        }
//        if(CURLE_OK == res) {
//            char *ct;
//            /* ask for the content-type */
//            res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
//            if((CURLE_OK == res) && ct)
//                printf("We received Content-Type: %s\n", ct);
//        }
//    }
////    // Follow HTTP redirects if necessary.
////    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
////
////    // Don't bother trying IPv6, which would increase DNS resolution time.
////    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
////
////    // Don't wait forever, time out after 10 seconds.
////    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
//
//
//
//    // Response information.
//    //int httpCode(0);
//    //std::unique_ptr<std::string> httpData(new std::string());
//
//    // Hook up data handling function.
////    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
//
//    // Hook up data container (will be passed as the last parameter to the
//    // callback handling function).  Can be any pointer type, since it will
//    // internally be passed as a void pointer.
////    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
//
//    // Run our HTTP GET command, capture the HTTP response code, and clean up.
////    curl_easy_perform(curl);
//    //curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
//    //curl_easy_cleanup(curl);
//
//    //char *val=new char[url.length()+1];
//    //strcpy((char *)val,url.c_str());
//
//
////    if (httpCode == 200)
////    {
//////        Log::debug("\nGot successful response from ");
//////        Log::debug(val);
////        return 2;
////    }
////    else
////    {
//////        Log::debug("Couldn't GET from ");
//////        Log::debug(val);
//////        Log::debug(" - exiting\n");
////        return -1;
////    }
//
//
//    //return httpCode;
//    //cout << endl << "Res : " << res << endl;
//    return 0;
//
//}
//
//
