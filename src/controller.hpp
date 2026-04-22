#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include "httpRequest.hpp"
#include "httpResponse.hpp"

HttpResponse indexHandler(const HttpRequest&);
HttpResponse echoHandler(const HttpRequest&);
HttpResponse userAgentHandler(const HttpRequest&);

#endif
