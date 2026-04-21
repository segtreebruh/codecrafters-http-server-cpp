#ifndef HTTP_HPP
#define HTTP_HPP

#include <string>
#include <iostream>

struct HTTPRequestHeader
{
  std::string host;
  std::string userAgent;
  std::string accept;

  HTTPRequestHeader() {}
  HTTPRequestHeader(std::string host, std::string userAgent, std::string accept)
      : host(host), userAgent(userAgent), accept(accept) {}

  friend std::ostream &operator<<(std::ostream &os, const HTTPRequestHeader &header)
  {
    os << header.host << ' ' << header.userAgent << ' ' << header.accept;
    return os;
  }
};

struct HTTPRequest
{
  std::string req;
  HTTPRequestHeader headers;
  std::string body;

  HTTPRequest() {}
  HTTPRequest(const std::string &);

  friend std::ostream &operator<<(std::ostream &os, const HTTPRequest &request)
  {
    os << request.req << request.headers << request.body << "\n";
    return os;
  }
};

struct HTTPResponseHeader
{
  std::string contentType = "Content-Type: text/plain\r\n";
  std::string contentLength;

  HTTPResponseHeader() {}
  HTTPResponseHeader(const std::string &);

  friend std::ostream &operator<<(std::ostream &os, const HTTPResponseHeader &header)
  {
    os << header.contentType << ' ' << header.contentLength << ' ';
    return os;
  }
};

struct HTTPResponse
{
  std::string status;
  HTTPResponseHeader header;
  std::string body;

  HTTPResponse() {}
  HTTPResponse(const HTTPRequest &);

  friend std::ostream &operator<<(std::ostream &os, const HTTPResponse &response)
  {
    os << response.status << response.header << response.body << "\n";
    return os;
  }
};

#endif