#ifndef HTTP_HPP
#define HTTP_HPP

#include "httpRequest.hpp"
#include "httpResponse.hpp"

HTTPResponse parseEchoResponse(HTTPRequest const&);
HTTPResponse parseUserAgentResponse(HTTPRequest const&);
HTTPResponse parseResponse(HTTPRequest const&);

#endif