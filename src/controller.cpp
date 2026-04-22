#include "controller.hpp"

HTTPResponse indexHandler(const HTTPRequest&) {
    return HTTPResponse("200 OK", HTTPResponseHeader(), "");
}

HTTPResponse echoHandler(const HTTPRequest& request) {
    size_t echoPos = request.req.find("/echo/");
    size_t httpPos = request.req.find(" HTTP/");
    if (echoPos == std::string::npos || httpPos == std::string::npos) {
        return HTTPResponse("404 Not Found", HTTPResponseHeader(), "");
    }

    std::string content = request.req.substr(echoPos + 6, httpPos - (echoPos + 6));
    return HTTPResponse("200 OK", HTTPResponseHeader::echo(request), content);
}

HTTPResponse userAgentHandler(HTTPRequest const& request) {
    std::string userAgent = request.header.userAgent;

    return HTTPResponse("200 OK", HTTPResponseHeader::userAgent(request), userAgent);
}
