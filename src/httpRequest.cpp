#include "httpRequest.hpp"

HttpRequest::HttpRequest(const std::string& request) {
    const std::string hostStr = "Host: ",
                      userAgentStr = "User-Agent: ",
                      acceptStr = "Accept: ",
                      acceptEncodingStr = "Accept-Encoding: ";

    size_t hostPos = request.find(hostStr);
    size_t userAgentPos = request.find(userAgentStr);
    size_t acceptPos = request.find(acceptStr);
    size_t acceptEncodingPos = request.find(acceptEncodingStr);

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

    std::string acceptEncoding;
    if (acceptEncodingPos != std::string::npos) {
        subheaderEndPos = request.find("\r\n", acceptEncodingPos);
        acceptEncoding = request.substr(
            acceptEncodingPos + acceptEncodingStr.size(),
            subheaderEndPos - acceptEncodingPos - acceptEncodingStr.size());
    }

    req = request.substr(0, hostPos - 2);

    size_t methodEndPos = request.find("/") - 2;
    size_t pathEndPos = request.find("HTTP") - 2;

    method = request.substr(0, methodEndPos + 1);
    path = request.substr(methodEndPos + 2, pathEndPos - (methodEndPos + 2) + 1);

    header = HttpRequestHeader(host, userAgent, accept, acceptEncoding);

    // header end with \r\n\r\n
    size_t headerEndPos = request.find("\r\n\r\n");
    body = request.substr(headerEndPos + 4);
}

std::string HttpRequest::str() const {
    return method + " " + path + " " + "HTTP/1.1" + "\n" +
           "Host: " + header.host + "\n" +
           "User-Agent: " + header.userAgent + "\n" +
           "Accept: " + header.accept + "\n\n" +
           "Accept-Encoding: " + header.acceptEncoding + "\n\n" +
           body;
}