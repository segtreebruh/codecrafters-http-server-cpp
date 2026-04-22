#include "controller.hpp"

HttpResponse indexHandler(const HttpRequest&) {
    return HttpResponse("200 OK", HttpResponseHeader(), "");
}

HttpResponse echoHandler(const HttpRequest& request) {
    size_t echoPos = request.req.find("/echo/");
    size_t httpPos = request.req.find(" HTTP/");
    if (echoPos == std::string::npos || httpPos == std::string::npos) {
        return HttpResponse("404 Not Found", HttpResponseHeader(), "");
    }

    std::string body = request.req.substr(echoPos + 6, httpPos - (echoPos + 6));
    HttpResponseHeader header =
        HttpResponseHeader("text/plain", static_cast<int>(body.size()));

    return HttpResponse("200 OK", header, body);
}

HttpResponse userAgentHandler(HttpRequest const& request) {
    std::string body = request.header.userAgent;
    HttpResponseHeader header = 
        HttpResponseHeader("text/plain", static_cast<int>(body.size()));

    return HttpResponse("200 OK", header, body);
}
