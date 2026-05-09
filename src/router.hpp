#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <functional>
#include <regex>
#include <string>
#include <vector>

#include "httpRequest.hpp"
#include "httpResponse.hpp"

using Handler = std::function<HttpResponse(HttpRequest const&)>;

/// @brief Route class. Contains info about a certain Route (method, pattern, handler)
struct Route {
    std::string method;
    std::regex pattern;
    Handler handler;

    Route(std::string const& method, std::string const& pattern, Handler handler)
        : method(method), pattern(pattern), handler(handler) {}
};

/// @brief Router class to contain multiple Routes. 
struct Router {
    void addRoute(std::string const&, std::string const&, Handler);
    HttpResponse dispatch(HttpRequest const&) const;
    std::vector<Route> routes;
};

#endif