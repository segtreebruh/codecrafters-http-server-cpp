#include "controller.hpp"

#include <fstream>
#include <sstream>

HttpResponse indexHandler(const HttpRequest&) {
    return HttpResponse("200 OK", HttpResponseHeader(), "");
}

HttpResponse echoHandler(const HttpRequest& request) {
    std::string body = request.path.substr(6); // strip "/echo/"
    return HttpResponse("200 OK", "text/plain", body, request.header.acceptEncodings);
}

HttpResponse userAgentHandler(HttpRequest const& request) {
    return HttpResponse("200 OK", "text/plain", request.header.userAgent, request.header.acceptEncodings);
}

HttpResponse FileController::get(HttpRequest const& request) const {
    std::string filename = request.path.substr(std::string("/files/").size());
    std::string filepath = directory + "/" + filename;

    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open())
        return HttpResponse("404 Not Found", HttpResponseHeader(), "");

    std::ostringstream ss;
    ss << file.rdbuf();
    return HttpResponse("200 OK", "application/octet-stream", ss.str(), request.header.acceptEncodings);
}

HttpResponse FileController::post(const HttpRequest& request) const {
    std::string filename = request.path.substr(std::string("/files/").size());
    std::string filepath = directory + "/" + filename;

    std::ofstream file(filepath, std::ios::binary);
    file << request.body;
    return HttpResponse("201 Created", HttpResponseHeader(), "");
}