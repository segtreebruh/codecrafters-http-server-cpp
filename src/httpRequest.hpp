#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>

struct HTTPRequestHeader {
    std::string host;
    std::string userAgent;
    std::string accept;

    HTTPRequestHeader(): host(""), userAgent(""), accept("") {}
    HTTPRequestHeader(std::string const& host, std::string const& userAgent, std::string const& accept)
        : host(host), userAgent(userAgent), accept(accept) {}
};

struct HTTPRequest {
    std::string req;
    HTTPRequestHeader header;
    std::string body;

    HTTPRequest(): req(""), header(HTTPRequestHeader()), body("") {}
    HTTPRequest(const std::string&);

    std::string str() const;
};

#endif