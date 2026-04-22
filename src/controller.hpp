#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include "httpRequest.hpp"
#include "httpResponse.hpp"

HTTPResponse indexHandler(const HTTPRequest&);
HTTPResponse echoHandler(const HTTPRequest&);
HTTPResponse userAgentHandler(const HTTPRequest&);

#endif
