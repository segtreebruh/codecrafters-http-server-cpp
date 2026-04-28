#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>

struct HttpRequestHeader {
    std::string host;
    std::string userAgent;
    std::string accept;
    std::string acceptEncoding;

    HttpRequestHeader() = default;
    HttpRequestHeader(std::string const& host, std::string const& userAgent,
                      std::string const& accept, std::string const& acceptEncoding)
        : host(host), userAgent(userAgent), accept(accept), acceptEncoding(acceptEncoding) {}
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