#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>

#include "httpRequest.hpp"

struct HttpResponseHeader {
    std::string contentType;
    int contentLength = 0;
    std::vector<std::string> _contentEncodings;
    std::string connection;

    HttpResponseHeader() = default;
    HttpResponseHeader(const std::string& contentType, int contentLength, std::vector<std::string> const& contentEncodings)
        : contentType(contentType), contentLength(contentLength), _contentEncodings(contentEncodings) {}
};

struct HttpResponse {
    std::string status;
    HttpResponseHeader header;
    std::string body;

    HttpResponse() = default;
    HttpResponse(const std::string& status,
                 HttpResponseHeader const& header, std::string const& body)
        : status(status), header(header), body(body) {}

    HttpResponse(std::string const&, std::string const&, std::string,
                 std::vector<std::string> const& = {});

    std::string str() const;
};

#endif