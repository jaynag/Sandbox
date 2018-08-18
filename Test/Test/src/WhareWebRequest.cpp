//
//  WhareWebRequest.cpp
//  Test
//
//  Created by Jayashree Nagarajan on 8/17/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

#include "WhareWebRequest.hpp"
#include "iostream"

string response_string = "";

std::size_t ResponseRecievedCallback(const char* in, size_t size, size_t num, string* out)
{
    const std::size_t totalBytes(size * num);
    cout << "\n Callback executed" ;
    cout << endl << in << endl;
    response_string = in;
    return totalBytes;
}

WhareWebRequest::WhareWebRequest()
{
    cout << "WhareWebRequest Constructor" << endl;
}

WhareWebRequest::~WhareWebRequest()
{
    cout << "WhareWebRequest Destructor" << endl;
}

string WhareWebRequest::Get(string endpoint, string client_id, function<void(string, int)> &&callback)
{
    struct curl_slist *headers = NULL;
    CURL *curl = NULL;
    curl  = curl_easy_init();
    int httpCode(0);
    cout << endl << "XXXX " << client_id << endl; 
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        //Set remote URL
        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
        headers = curl_slist_append(headers, (const char *)auth_headers.c_str());
        headers = curl_slist_append(headers, (const char *)client_id.c_str());
        CURLcode res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ResponseRecievedCallback);
        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    }
    
    callback(response_string, httpCode);

    return response_string;
}
void WhareWebRequest::Post(string endpoint, string value, function<void(string, int)> &&callback)
{
    struct curl_slist *headers = NULL;
    CURL *curl = NULL;
    curl  = curl_easy_init();
    int httpCode(0);
    
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        //Set remote URL
        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, value.c_str());
        
        headers = curl_slist_append(headers, (const char *)auth_headers.c_str());
        
        CURLcode res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ResponseRecievedCallback);
        
        res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    }
    
    callback(response_string, httpCode);
}

void WhareWebRequest::AddHeaderFields(string n, string v)
{
    auth_headers = n + ": " + v;
}



