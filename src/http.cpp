#include "http.hpp"

#include <iostream>

HTTPRequest::HTTPRequest(const std::string& request) {
  const std::string hostStr = "Host: ",
                    userAgentStr = "User-Agent: ",
                    acceptStr = "Accept: ";

  size_t hostPos = request.find(hostStr);
  size_t userAgentPos = request.find(userAgentStr);
  size_t acceptPos = request.find(acceptStr);

  size_t subheaderEndPos;

  // for each subheader, find next \r\n and subtract to get subheader
  subheaderEndPos = request.find("\r\n", hostPos);
  const std::string host = request.substr(hostPos + hostStr.size(),
                                          subheaderEndPos - hostPos - hostStr.size());

  subheaderEndPos = request.find("\r\n", userAgentPos);
  const std::string userAgent = request.substr(userAgentPos + userAgentStr.size(),
                                               subheaderEndPos - userAgentPos - userAgentStr.size());

  subheaderEndPos = request.find("\r\n", acceptPos);
  const std::string accept = request.substr(acceptPos + acceptStr.size(),
                                            subheaderEndPos - acceptPos - acceptStr.size());

  req = request.substr(0, hostPos - 2);
  headers = HTTPRequestHeader(host, userAgent, accept);

  // header end with \r\n\r\n
  size_t headerEndPos = request.find("\r\n\r\n");
  body = request.substr(headerEndPos + 4);
}

std::string HTTPRequest::str() const {
  return req + "\n" +
         "Host: " + headers.host + "\n" +
         "User-Agent: " + headers.userAgent + "\n" +
         "Accept: " + headers.accept + "\n\n" +
         body;
}

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
  ;
  std::string userAgent = request.headers.userAgent;

  return HTTPResponseHeader("text/plain", static_cast<int>(userAgent.size()));
}

HTTPResponse parseResponse(HTTPRequest const& request) {
  if (request.req.find("GET / ") != std::string::npos)
    return HTTPResponse("200 OK", HTTPResponseHeader("", 0), "");
  if (request.req.find("GET /echo/") != std::string::npos)
    return parseEchoResponse(request);
  if (request.req.find("GET /user-agent") != std::string::npos)
    return parseUserAgentResponse(request);

  return HTTPResponse("404 Not Found", HTTPResponseHeader(), "");
}

HTTPResponse parseEchoResponse(HTTPRequest const& request) {
  size_t echoPos = request.req.find("/echo/");
  size_t httpPos = request.req.find(" HTTP/");
  if (echoPos == std::string::npos || httpPos == std::string::npos) {
    return HTTPResponse("404 Not Found", HTTPResponseHeader(), "");
  }

  std::string content = request.req.substr(echoPos + 6, httpPos - (echoPos + 6));
  return HTTPResponse("200 OK", HTTPResponseHeader::echo(request), content);
}

HTTPResponse parseUserAgentResponse(HTTPRequest const& request) {
  std::string userAgent = request.headers.userAgent;

  return HTTPResponse("200 OK", HTTPResponseHeader::userAgent(request), userAgent);
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
