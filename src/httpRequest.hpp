#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>
#include <vector>

/**
 * HttpRequestHeader class
 */
struct HttpRequestHeader {
    std::string host;
    std::string userAgent;
    std::string accept;
    std::vector<std::string> acceptEncodings;
    std::string connection;

    HttpRequestHeader() = default;
    HttpRequestHeader(std::string const& host, std::string const& userAgent,
                      std::string const& accept, std::vector<std::string> const& acceptEncodings,
                      std::string const& connection)
        : host(host), userAgent(userAgent), accept(accept), 
        acceptEncodings(acceptEncodings), connection(connection) {}
};

/**
 * HttpRequest class 
 * 
 * method: GET/POST/DELETE/etc.
 * path: path of request. e.g. "/", "/index", "/echo/something", etc.
 * header: HttpRequestHeader
 * body: request body
 * 
 */
struct HttpRequest {
    std::string method;
    std::string path;
    HttpRequestHeader header;
    std::string body;

    HttpRequest() = default;
    HttpRequest(const std::string&);

    std::string str() const;
};

#endif