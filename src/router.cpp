#include "router.hpp"

void Router::addRoute(std::string const& method, std::string const& pattern, Handler handler) {
    routes.push_back({method, pattern, handler});
}

HTTPResponse Router::dispatch(HTTPRequest const& request) const {
    for (const auto& route: routes) {
        if (route.method != request.method) continue;

        bool match = std::regex_search(request.path, route.pattern);

        if (match) return route.handler(request);
    }

    return HTTPResponse("404 Not Found", HTTPResponseHeader(), "");
}

