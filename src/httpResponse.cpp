#include "httpResponse.hpp"

HttpResponseHeader::HttpResponseHeader(std::string const& contentType, int contentLength,
                                       std::string const& contentEncoding)
    : contentType(contentType),
      contentLength(contentLength),
      contentEncoding(contentEncoding) {}

std::string HttpResponse::str() const {
    std::string raw = "HTTP/1.1 " + status + "\r\n";

    if (header.contentType.size()) {
        // only accept gzip encoding
        if (header.contentEncoding == "gzip") 
            raw += "Content-Encoding: " + header.contentEncoding + "\r\n";
        raw += "Content-Type: " + header.contentType + "\r\n";
        raw += "Content-Length: " + std::to_string(header.contentLength);
    }
    raw += "\r\n\r\n";
    raw += body;
    return raw;
}