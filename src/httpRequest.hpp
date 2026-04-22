#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>

struct HttpRequestHeader {
    std::string host;
    std::string userAgent;
    std::string accept;

    HttpRequestHeader(): host(""), userAgent(""), accept("") {}
    HttpRequestHeader(std::string const& host, std::string const& userAgent, std::string const& accept)
        : host(host), userAgent(userAgent), accept(accept) {}
};

struct HttpRequest {
    std::string method;
    std::string path;
    std::string req;
    HttpRequestHeader header;
    std::string body;

    HttpRequest(): req(""), method(""), path(""), header(HttpRequestHeader()), body("") {}
    HttpRequest(const std::string&);

    std::string str() const;
};

#endif