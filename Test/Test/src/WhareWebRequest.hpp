//
//  WhareWebRequest.hpp
//  Test
//
//  Created by Jayashree Nagarajan on 8/17/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

#ifndef WhareWebRequest_hpp
#define WhareWebRequest_hpp

#include <stdio.h>
#include <string>
#include <curl/curl.h>
#include <future>

#endif /* WhareWebRequest_hpp */

using namespace std;

class WhareWebRequest
{
private:
    string auth_headers = "";
    
public:
    WhareWebRequest();
    ~WhareWebRequest();
    
    void Post(string endpoint, string value, function<void(string, int)> &&callback);
    string Get(string endpoint, string client_id, function<void(string, int)> &&callback);
    //string get(string endpoint);
    
    void AddHeaderFields(string n, string v);
    
};
