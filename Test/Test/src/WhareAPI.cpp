//
//  WhareAPI.cpp
//  Test
//
//  Created by Jayashree Nagarajan on 8/17/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

#include "WhareAPI.hpp"

WhareAPI::WhareAPI()
{
    cout << "Instantiating WhareAPI class" << endl;
}

WhareAPI::~WhareAPI()
{
    cout << "WhareAPI object destroyed!" << endl;
}

void WhareAPI::RegisterApp(KeyHandler * key_handler)
{
    _key_handler = key_handler;
    string guid = "";
    int result = 0;
    AddObject(_appInstanceEndpoint, "user_id = Jayashree", [&guid, &result](string s, int v){
        
        result = v;
        if(result == 201)
        {
            //isRegistered = true;
            guid = s;
            cout << "Now you can call other GET APIs" << s;
        }
        else
        {
            cout << "Error registering user";
        }
    });
    
}

void WhareAPI::ProcessWebRequest(int httpCode, function<void(string, int)> &&callback)
{
    if(httpCode == 400)
    {
        callback("",httpCode);
    }
    else callback("client id recieved", httpCode);
}

void WhareAPI::AddObject(string endpoint, string client_info, function<void(string, int)> &&callback)
{
    WhareWebRequest *www = new WhareWebRequest();
    string headers = GetAuthHeaders();
    www->AddHeaderFields(authorization_name, headers);
    
    string guid = "";
    int  httpCode(0);
    
    www->Post(endpoint, "user_id: Jayashree", [&guid, &httpCode](string m, int v){
        if(v == 201)
        {
            cout << "Client Id: " << m;
            guid = m;
        }
        cout << endl << m << "HTTP CODE: " << v;
        httpCode = v;
    });
    
    callback(guid, httpCode);
    
}

string WhareAPI::GetAuthHeaders()
{
    string nonce = _key_handler->GenerateNonce();
    return "Token " + _key_handler->GetLicenceKey() + " " + _key_handler->GenerateSignature(nonce) + " " + nonce;
    
}
