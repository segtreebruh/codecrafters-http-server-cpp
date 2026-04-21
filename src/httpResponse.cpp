#include "httpResponse.hpp"

HTTPResponseHeader::HTTPResponseHeader(std::string const& contentType, int contentLength)
    : contentType(contentType), contentLength(contentLength) {}

HTTPResponseHeader HTTPResponseHeader::echo(const HTTPRequest& request) {
    size_t echoPos = request.req.find("/echo/");
    size_t httpPos = request.req.find(" HTTP/");
    if (echoPos == std::string::npos || httpPos == std::string::npos)
        return HTTPResponseHeader("text/plain", 0);

    std::string content = request.req.substr(echoPos + 6, httpPos - (echoPos + 6));
    return HTTPResponseHeader("text/plain", static_cast<int>(content.size()));
}

HTTPResponseHeader HTTPResponseHeader::userAgent(const HTTPRequest& request) {
    std::string userAgent = request.header.userAgent;

    return HTTPResponseHeader("text/plain", static_cast<int>(userAgent.size()));
}

std::string HTTPResponse::str() const {
    std::string raw = "HTTP/1.1 " + status + "\r\n";

    if (header.contentType.size()) {
        raw += "Content-Type: " + header.contentType + "\r\n";
        raw += "Content-Length: " + std::to_string(header.contentLength);
    }
    raw += "\r\n\r\n";
    raw += body;
    return raw;
}