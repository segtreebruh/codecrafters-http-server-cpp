#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>

#include "httpRequest.hpp"

struct HttpResponseHeader {
    std::string contentType;
    int contentLength = 0;
    std::string contentEncoding;

    HttpResponseHeader() = default;
    HttpResponseHeader(const std::string&, int, std::string const&);
};

struct HttpResponse {
    std::string status;
    HttpResponseHeader header;
    std::string body;

    HttpResponse() = default;
    HttpResponse(const std::string& status,
                 HttpResponseHeader const& header, std::string const& body)
        : status(status), header(header), body(body) {}

    std::string str() const;
};

#endif