#include "http.hpp"

#include "httpRequest.hpp"
#include "httpResponse.hpp"

HTTPResponse parseResponse(HTTPRequest const& request) {
    if (request.req.find("GET / ") != std::string::npos)
        return HTTPResponse("200 OK", HTTPResponseHeader(), "");
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
    std::string userAgent = request.header.userAgent;

    return HTTPResponse("200 OK", HTTPResponseHeader::userAgent(request), userAgent);
}