#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>

#include "httpRequest.hpp"

struct HttpResponseHeader {
    std::string contentType;
    int contentLength;

    HttpResponseHeader(): contentType(""), contentLength(0) {}
    HttpResponseHeader(const std::string&, int);
};

struct HttpResponse {
    std::string status;
    HttpResponseHeader header;
    std::string body;

    HttpResponse(): status(""), header(HttpResponseHeader()), body("") {}
    HttpResponse(const std::string& status,
                 HttpResponseHeader const& header, std::string const& body)
        : status(status), header(header), body(body) {}

    std::string str() const;
};

#endif