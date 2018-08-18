//
//  WhareAPI.cpp
//  Test
//
//  Created by Jayashree Nagarajan on 8/17/18.
//  Copyright © 2018 SamsungNext. All rights reserved.
//

#include "WhareAPI.hpp"

using nlohmann::json;

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
    string client_id = "";
    WhareRequestStatus result;
    AddObject(_appInstanceEndpoint, "user_id = Jayashree", [&client_id, &result](string guid, WhareRequestStatus res){
        
        cout << "Client ID: " << guid;
        result = res;
        client_id = "client_id: " + guid;
    });
    
    if(result == WhareRequestStatus::SUCCESS)
    {
        
        LoadVirtualSpace(_virtualSpaceEndpoint, client_id);
    }
    
}

void WhareAPI::ProcessWebRequest(int httpCode, function<void(string, int)> &&callback)
{
    if(httpCode == 400)
    {
        callback("",httpCode);
    }
    else callback("client id recieved", httpCode);
}

void WhareAPI::AddObject(string endpoint, string client_info, function<void(string, WhareRequestStatus)> &&callback)
{
    WhareWebRequest *www = new WhareWebRequest();
    string headers = GetAuthHeaders();
    www->AddHeaderFields(authorization_name, headers);
//    bool isRegistered = false;
//    string client_guid;
    www->Post(endpoint, "user_id: Jayashree", [&](string guid, int http_code){
        if(http_code == 201)
        {
            json json_object = json::parse(guid);
            callback(json_object["client_guid"], WhareRequestStatus::SUCCESS);
//            isRegistered = true;
//            client_guid = guid;
        }
        else
        {
            //TODO: Add more clauses later
            callback("", WhareRequestStatus::UNAUTHORIZED);
        }
    });
    
}

string WhareAPI::LoadVirtualSpace(string endpoint, string client_id)
{
    WhareWebRequest *www = new WhareWebRequest();
    string headers = GetAuthHeaders();
    www->AddHeaderFields(authorization_name, headers);
    string response_string = www->Get(endpoint, client_id, [&](string response, int code){
        cout << response_string;
    });
    
    return response_string;
}

string WhareAPI::GetAuthHeaders()
{
    string nonce = _key_handler->GenerateNonce();
    return "Token " + _key_handler->GetLicenceKey() + " " + _key_handler->GenerateSignature(nonce) + " " + nonce;
    
}
