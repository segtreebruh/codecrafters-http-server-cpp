#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>
#include "httpRequest.hpp"
#include "httpResponse.hpp"

HttpResponse indexHandler(const HttpRequest&);
HttpResponse echoHandler(const HttpRequest&);
HttpResponse userAgentHandler(const HttpRequest&);

struct FileController {
    std::string directory;

    FileController(std::string const& directory): directory(directory) {}
    HttpResponse get(const HttpRequest&) const;
    HttpResponse post(const HttpRequest&) const;
};

#endif
