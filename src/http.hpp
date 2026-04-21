#ifndef HTTP_HPP
#define HTTP_HPP

#include <iostream>
#include <string>

struct HTTPRequestHeader {
  std::string host;
  std::string userAgent;
  std::string accept;

  HTTPRequestHeader() {}
  HTTPRequestHeader(std::string const& host, std::string const& userAgent, std::string const& accept)
      : host(host), userAgent(userAgent), accept(accept) {}
};

struct HTTPRequest {
  std::string req;
  HTTPRequestHeader headers;
  std::string body;

  HTTPRequest() {}
  HTTPRequest(const std::string&);
  std::string str() const;
};

struct HTTPResponseHeader {
  std::string contentType;
  int contentLength;

  HTTPResponseHeader() {}
  HTTPResponseHeader(const std::string&, int);

  static HTTPResponseHeader echo(const HTTPRequest&);
  static HTTPResponseHeader userAgent(const HTTPRequest&);
};

struct HTTPResponse {
  std::string status;
  HTTPResponseHeader header;
  std::string body;

  HTTPResponse() {}
  HTTPResponse(const std::string& status,
               HTTPResponseHeader const& header, std::string const& body)
      : status(status), header(header), body(body) {}

  std::string str() const;
};

HTTPResponse parseEchoResponse(HTTPRequest const&);
HTTPResponse parseUserAgentResponse(HTTPRequest const&);
HTTPResponse parseResponse(HTTPRequest const&);

#endif