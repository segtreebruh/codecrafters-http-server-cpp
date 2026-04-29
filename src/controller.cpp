#include "controller.hpp"
#include <fstream>
#include <sstream>
#include "gzip.hpp"

HttpResponse indexHandler(const HttpRequest&) {
    return HttpResponse("200 OK", HttpResponseHeader(), "");
}

HttpResponse echoHandler(const HttpRequest& request) {
    std::string body = request.path.substr(6); // strip "/echo/"
    for (const auto& s: request.header.acceptEncodings) {
        if (s == "gzip") body = compress_gzip(body);
    }

    HttpResponseHeader header = HttpResponseHeader(
        "text/plain",
        static_cast<int>(body.size()),
        request.header.acceptEncodings
    );

    return HttpResponse("200 OK", header, body);
}

HttpResponse userAgentHandler(HttpRequest const& request) {
    std::string body = request.header.userAgent;

    HttpResponseHeader header;
    header.contentType = "text/plain";
    header.contentLength = static_cast<int>(body.size());
    if (request.header.acceptEncodings.size()) 
        header._contentEncodings = request.header.acceptEncodings;

    return HttpResponse("200 OK", header, body);
}

HttpResponse FileController::get(HttpRequest const& request) const {
    std::string filename = request.path.substr(std::string("/files/").size());
    std::string filepath = directory + "/" + filename;

    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        return HttpResponse("404 Not Found", HttpResponseHeader(), "");
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string body = ss.str();

    HttpResponseHeader header;
    header.contentType = "application/octet-stream";
    header.contentLength = static_cast<int>(body.size());
    if (request.header.acceptEncodings.size()) 
        header._contentEncodings = request.header.acceptEncodings;

    return HttpResponse("200 OK", header, body);
}

HttpResponse FileController::post(const HttpRequest& request) const {
    std::string filename = request.path.substr(std::string("/files/").size());
    std::string filepath = directory + "/" + filename;

    std::ofstream file(filepath, std::ios::binary);
    file << request.body;

    return HttpResponse("201 Created", HttpResponseHeader(), "");
}