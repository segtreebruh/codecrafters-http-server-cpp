#include "httpResponse.hpp"

HttpResponseHeader::HttpResponseHeader(std::string const& contentType, int contentLength,
                                       std::vector<std::string> const& contentEncodings)
    : contentType(contentType),
      contentLength(contentLength) {
    for (const auto& s : contentEncodings) {
        if (s == "gzip") _contentEncodings.push_back(s);
    }
}

std::string HttpResponse::str() const {
    std::string raw = "HTTP/1.1 " + status + "\r\n";

    if (header.contentType.size()) {
        if (header._contentEncodings.size()) {
            std::string encodings;
            for (const auto& s : header._contentEncodings) {
                encodings += (encodings.empty() ? "" : ", ") + s;
            }
            raw += "Content-Encoding: " + encodings + "\r\n";
        }
        raw += "Content-Type: " + header.contentType + "\r\n";
        raw += "Content-Length: " + std::to_string(header.contentLength);
    }
    raw += "\r\n\r\n";
    raw += body;
    return raw;
}