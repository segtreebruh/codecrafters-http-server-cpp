#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>

#include "httpRequest.hpp"

struct HTTPResponseHeader {
    std::string contentType;
    int contentLength;

    HTTPResponseHeader() {}
    HTTPResponseHeader(const std::string&, int);

    static HTTPResponseHeader echo(const HTTPRequest&);
    static HTTPResponseHeader userAgent(const HTTPRequest&);
};

struct HTTPResponse {
    std::string status;
    HTTPResponseHeader header;
    std::string body;

    HTTPResponse() {}
    HTTPResponse(const std::string& status,
                 HTTPResponseHeader const& header, std::string const& body)
        : status(status), header(header), body(body) {}

    std::string str() const;
};

#endif