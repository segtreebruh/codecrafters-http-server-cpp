#include "httpResponse.hpp"

#include "gzip.hpp"

/**
 * HttpResponse constructor. 
 * 
 * Only constructed after most logic is done and waiting to return 
 * (hence the field "status" - status is determined before object is created).
 * 
 * Can handle gzip compression before returning final result.
 */
HttpResponse::HttpResponse(std::string const& status,
                           std::string const& contentType, std::string body,
                           std::vector<std::string> const& encodings) : status(status) {
    std::vector<std::string> contentEncoding;

    for (const auto& s : encodings) {
        if (s == "gzip") {
            body = compress_gzip(body);
            contentEncoding.push_back("gzip");
        }
    }

    this->body = body;
    header = HttpResponseHeader(contentType,
                                static_cast<int>(this->body.size()),
                                contentEncoding);
}

/**
 * HttpResponse string representation. 
 *
 * Format data before sending to server. 
 */
std::string HttpResponse::str() const {
    std::string raw = "HTTP/1.1 " + status + "\r\n";

    if (!header.connection.empty())
        raw += "Connection: " + header.connection + "\r\n";
    if (header.contentType.size()) {
        if (header._contentEncodings.size()) {
            std::string encodings;
            for (const auto& s : header._contentEncodings) {
                encodings += (encodings.empty() ? "" : ", ") + s;
            }
            raw += "Content-Encoding: " + encodings + "\r\n";
        }
        raw += "Content-Type: " + header.contentType + "\r\n";
        raw += "Content-Length: " + std::to_string(header.contentLength) + "\r\n";
    }
    raw += "\r\n";
    raw += body;
    return raw;
}