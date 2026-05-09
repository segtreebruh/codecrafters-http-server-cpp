#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>

#include "httpRequest.hpp"

/**
 * HttpResponseHeader class.
 * Containing response headers.
 */
struct HttpResponseHeader {
    std::string contentType;
    int contentLength = 0;

    /// @brief Content encodings read from HttpRequest. 
    /// Currently only support gzip
    std::vector<std::string> _contentEncodings;

    /// @brief Used for closing connection during a keep-alive connection
    std::string connection;

    HttpResponseHeader() = default;
    HttpResponseHeader(const std::string& contentType, int contentLength, std::vector<std::string> const& contentEncodings)
        : contentType(contentType), contentLength(contentLength), _contentEncodings(contentEncodings) {}
};

/**
 * HttpResponse class. 
 * 
 */
struct HttpResponse {
    /// @brief status code (200 OK, 404 Not Found, etc.)
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