#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>
#include <vector>

struct HttpRequestHeader {
    std::string host;
    std::string userAgent;
    std::string accept;
    std::vector<std::string> acceptEncodings;

    HttpRequestHeader() = default;
    HttpRequestHeader(std::string const& host, std::string const& userAgent,
                      std::string const& accept, std::vector<std::string> const& acceptEncodings)
        : host(host), userAgent(userAgent), accept(accept), acceptEncodings(acceptEncodings) {}
};

struct HttpRequest {
    std::string method;
    std::string path;
    std::string req;
    HttpRequestHeader header;
    std::string body;

    HttpRequest() = default;
    HttpRequest(const std::string&);

    std::string str() const;
};

#endif