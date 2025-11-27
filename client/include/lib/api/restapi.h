#pragma once
#include "httplib.h"
#include <iostream>


enum HEADERS {
    JSON
};

class rest_client
{
//---------------------------------
private:
std::string base_url;
httplib::Client* client;

public:
//---------------------------------
rest_client();
~rest_client();

// http endpoint wrappers 
auto send_get(const std::string& endpoint);
auto send_post(const std::string& endpoint, HEADERS headers, std::string body);

};