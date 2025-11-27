#include "../../../include/lib/api/restapi.h"
#include "httplib.h"
#include <cstdlib>
#include <iostream>
#define CLIENT rest_client

// -------------------------------------
// implement http wrappers
// -------------------------------------
auto CLIENT::send_get(const std::string& endpoint)
{
    if (!this->client) {
        std::cerr << "ERROR: Client is null!" << std::endl;
        return httplib::Result(nullptr, httplib::Error::Unknown);
    }
    
    std::cout << "Making GET request to endpoint: " << endpoint << std::endl;
    auto res = this->client->Get(endpoint);
    
    if (res) {
        std::cout << "Response status: " << res->status << std::endl;
        std::cout << "Response body: " << res->body << std::endl;
    } else {
        std::cerr << "ERROR: Request failed - no response received" << std::endl;
        auto err = res.error();
        std::cerr << "Error type: " << static_cast<int>(err) << std::endl;
        
        // Print error descriptions
        switch(err) {
            case httplib::Error::Success:
                std::cerr << "Error: Success (unexpected)" << std::endl;
                break;
            case httplib::Error::Unknown:
                std::cerr << "Error: Unknown" << std::endl;
                break;
            case httplib::Error::Connection:
                std::cerr << "Error: Connection failed - server may not be running or wrong address/port" << std::endl;
                break;
            case httplib::Error::ConnectionTimeout:
                std::cerr << "Error: Connection timeout - server not responding" << std::endl;
                break;
            case httplib::Error::BindIPAddress:
                std::cerr << "Error: Bind IP address failed" << std::endl;
                break;
            case httplib::Error::Read:
                std::cerr << "Error: Read error" << std::endl;
                break;
            case httplib::Error::Write:
                std::cerr << "Error: Write error" << std::endl;
                break;
            case httplib::Error::ExceedRedirectCount:
                std::cerr << "Error: Exceeded redirect count" << std::endl;
                break;
            case httplib::Error::Canceled:
                std::cerr << "Error: Canceled" << std::endl;
                break;
            case httplib::Error::SSLConnection:
                std::cerr << "Error: SSL connection error" << std::endl;
                break;
            case httplib::Error::SSLLoadingCerts:
                std::cerr << "Error: SSL loading certs error" << std::endl;
                break;
            case httplib::Error::SSLServerVerification:
                std::cerr << "Error: SSL server verification error" << std::endl;
                break;
            case httplib::Error::UnsupportedMultipartBoundaryChars:
                std::cerr << "Error: Unsupported multipart boundary chars" << std::endl;
                break;
            default:
                std::cerr << "Error: Other error" << std::endl;
        }
    }
    
    return res;
}

auto CLIENT::send_post(const std::string& endpoint, HEADERS headers, std::string body)
{
    if (!this->client) {
        std::cerr << "ERROR: Client is null!" << std::endl;
        return httplib::Result(nullptr, httplib::Error::Unknown);
    }
    
    // Convert HEADERS enum to content type string
    std::string content_type;
    switch(headers) {
        case JSON:
            content_type = "application/json";
            break;
        default:
            content_type = "application/json"; // default to JSON
            break;
    }
    
    // Use the Post method that takes: path, body, content_type
    auto res = this->client->Post(endpoint, body, content_type);
    
    if (res) {
        std::cout << "Response status: " << res->status << std::endl;
        std::cout << "Response body: " << res->body << std::endl;
    } else {
        std::cerr << "ERROR: POST request failed - no response received" << std::endl;
        auto err = res.error();
        std::cerr << "Error type: " << static_cast<int>(err) << std::endl;
    }
    
    return res;
}


// -------------------------------------
// constructors
// -------------------------------------
CLIENT::rest_client()
{
    char* base_url_env = getenv("REST_BASE_URL");
    if (!base_url_env) 
    {
        std::cerr << "ERROR: REST_BASE_URL environment variable not set!" << std::endl;
        this->base_url = "";
        this->client = nullptr;
        return;
    }
    
    this->base_url = std::string(base_url_env);
    
    // Add http:// prefix if not present
    std::string full_url = this->base_url;
    if (!full_url.empty() && full_url.find("http://") != 0 && full_url.find("https://") != 0) {
        full_url = "http://" + full_url;
    }

    this->client = new httplib::Client(full_url);
    
    if (!this->client) 
    {
        std::cerr << "ERROR: Failed to create httplib client!" << std::endl;
        return;
    }
    
    // Set timeout
    this->client->set_connection_timeout(5, 0); // 5 seconds
    this->client->set_read_timeout(5, 0); // 5 seconds
}


//------------------------------------------------------
CLIENT::~rest_client(){}