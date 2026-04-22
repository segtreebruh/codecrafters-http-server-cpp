#include "httpResponse.hpp"

HttpResponseHeader::HttpResponseHeader(std::string const& contentType, int contentLength)
    : contentType(contentType), contentLength(contentLength) {}

std::string HttpResponse::str() const {
    std::string raw = "HTTP/1.1 " + status + "\r\n";

    if (header.contentType.size()) {
        raw += "Content-Type: " + header.contentType + "\r\n";
        raw += "Content-Length: " + std::to_string(header.contentLength);
    }
    raw += "\r\n\r\n";
    raw += body;
    return raw;
}