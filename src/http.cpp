#include "http.hpp"

#include <iostream>

HTTPRequest::HTTPRequest(const std::string &request)
{
    size_t reqEndPos = request.find("\r\n");
    size_t hostEndPos = request.find("\r\n", reqEndPos + 1);
    size_t userAgentEndPos = request.find("\r\n", hostEndPos + 1);
    size_t acceptEndPos = request.find("\r\n", acceptEndPos + 1);

    // header end marked with extra \r\n
    size_t headersEndPos = request.find("\r\n\r\n");

    // if fail: return nothing
    if (reqEndPos == std::string::npos || headersEndPos == std::string::npos)
        return;

    req = request.substr(0, reqEndPos);
    headers = HTTPRequestHeader(
        request.substr(reqEndPos + 2, hostEndPos - reqEndPos - 2),
        request.substr(hostEndPos + 2, userAgentEndPos - hostEndPos - 2),
        request.substr(userAgentEndPos, acceptEndPos - userAgentEndPos - 2));
    body = request.substr(headersEndPos + 4);
}

HTTPResponse::HTTPResponse(const HTTPRequest& request) 
{
    
}