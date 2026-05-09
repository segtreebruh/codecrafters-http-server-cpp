#include "httpRequest.hpp"

#include <sstream>
#include <vector>

/**
 * HttpRequest constructor
 * 
 * @param request: raw request string
 * @return void
 * @result Set up a HttqRequest object by parsing raw request string
 */
HttpRequest::HttpRequest(const std::string& request) {
    const std::string hostStr = "Host: ",
                      userAgentStr = "User-Agent: ",
                      acceptStr = "Accept: ",
                      acceptEncodingStr = "Accept-Encoding: ", 
                      connectionStr = "Connection: ";

    auto extractHeader = [&](const std::string& key) -> std::string {
        size_t pos = request.find(key);
        if (pos == std::string::npos) return "";
        size_t end = request.find("\r\n", pos);
        if (end == std::string::npos) end = request.size();
        return request.substr(pos + key.size(), end - pos - key.size());
    };

    const std::string host = extractHeader(hostStr);
    const std::string userAgent = extractHeader(userAgentStr);
    const std::string accept = extractHeader(acceptStr);
    const std::string encoding = extractHeader(acceptEncodingStr);
    const std::string connection = extractHeader(connectionStr);

    std::vector<std::string> acceptEncoding;
    std::istringstream ss(encoding);
    std::string token;
    while (std::getline(ss, token, ',')) {
        size_t start = token.find_first_not_of(' ');
        if (start != std::string::npos)
            acceptEncoding.push_back(token.substr(start));
    }

    size_t methodEndPos = request.find("/") - 2;
    size_t pathEndPos = request.find("HTTP") - 2;

    method = request.substr(0, methodEndPos + 1);
    path = request.substr(methodEndPos + 2, pathEndPos - (methodEndPos + 2) + 1);

    header = HttpRequestHeader(host, userAgent, accept, acceptEncoding, connection);

    // header end with \r\n\r\n
    size_t headerEndPos = request.find("\r\n\r\n");
    body = request.substr(headerEndPos + 4);
}

/**
 * HttpRequest string representation. 
 * 
 * @return string representation of HttpRequest, with all fields formatted
 */
std::string HttpRequest::str() const {
    std::string acceptEncoding;
    for (const auto& x : header.acceptEncodings)
        acceptEncoding += (acceptEncoding.empty() ? "" : ", ") + x;

    return method + " " + path + " HTTP/1.1\n" +
           "Host: " + header.host + "\n" +
           "User-Agent: " + header.userAgent + "\n" +
           "Accept: " + header.accept + "\n" +
           (acceptEncoding.empty() ? "" : "Accept-Encoding: " + acceptEncoding + "\n") + 
           "Connection: " + header.connection + "\n" + 
           "\n" + body;
}