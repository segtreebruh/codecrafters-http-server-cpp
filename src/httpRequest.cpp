#include "httpRequest.hpp"

HTTPRequest::HTTPRequest(const std::string& request) {
    const std::string hostStr = "Host: ",
                      userAgentStr = "User-Agent: ",
                      acceptStr = "Accept: ";

    size_t hostPos = request.find(hostStr);
    size_t userAgentPos = request.find(userAgentStr);
    size_t acceptPos = request.find(acceptStr);

    size_t subheaderEndPos;

    // for each subheader, find next \r\n and subtract to get subheader
    subheaderEndPos = request.find("\r\n", hostPos);
    const std::string host = request.substr(hostPos + hostStr.size(),
                                            subheaderEndPos - hostPos - hostStr.size());

    subheaderEndPos = request.find("\r\n", userAgentPos);
    const std::string userAgent = request.substr(userAgentPos + userAgentStr.size(),
                                                 subheaderEndPos - userAgentPos - userAgentStr.size());

    subheaderEndPos = request.find("\r\n", acceptPos);
    const std::string accept = request.substr(acceptPos + acceptStr.size(),
                                              subheaderEndPos - acceptPos - acceptStr.size());

    req = request.substr(0, hostPos - 2);
    headers = HTTPRequestHeader(host, userAgent, accept);

    // header end with \r\n\r\n
    size_t headerEndPos = request.find("\r\n\r\n");
    body = request.substr(headerEndPos + 4);
}

std::string HTTPRequest::str() const {
    return req + "\n" +
           "Host: " + headers.host + "\n" +
           "User-Agent: " + headers.userAgent + "\n" +
           "Accept: " + headers.accept + "\n\n" +
           body;
}