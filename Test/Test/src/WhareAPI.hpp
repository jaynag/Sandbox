//
//  WhareAPI.hpp
//  Test
//
//  Created by Jayashree Nagarajan on 8/17/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

#ifndef WhareAPI_hpp
#define WhareAPI_hpp

#include <stdio.h>
#include <string>
#include "KeyHandler.hpp"
#include "WhareWebRequest.hpp"
#include "json/json.hpp"
#endif /* WhareAPI_hpp */

using namespace std;

enum WhareRequestStatus {
    
    SUCCESS,
    UNAUTHORIZED,
    COULD_NOT_PARSE,
    NOT_FOUND,
    TIMED_OUT,
    UNKNOWN_ERROR
};


class WhareAPI
{
private:
    const string ApiAddress = "https://sandboxapi.whare.cloud/api/v0.1/";
    const string _virtualSpaceEndpoint = ApiAddress + "ar/virtualspace/";
    const string _appInstanceEndpoint = ApiAddress + "app/instance/";
    
    const string authorization_name = "Authorization";
    const string client_id_name = "client_id";
    
    struct ClientInfo
    {
        string guid;
        int result;
    };
    
    void ProcessWebRequest(int, function<void(string, int)> &&callback);
    void AddObject(string endpoint, string client_info, function<void(string, WhareRequestStatus)> &&callback);
    string LoadVirtualSpace(string endpoint, string client_id);
    string GetAuthHeaders();
    
    KeyHandler *_key_handler;
    bool isRegistered = false;
    
    
public:
    WhareAPI();
    ~WhareAPI();
    
    //void RegisterApp(ClientInfo client_info, KeyHandler * key_handler, function<void(string, int)> &&callback);
    void RegisterApp(KeyHandler * key_handler);
    
};


