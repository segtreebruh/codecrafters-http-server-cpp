#include "router.hpp"

/// @brief Bind a request (method-pattern) to a handler.
/// @param method GET/POST/etc
/// @param pattern 
/// @param handler Controller function
void Router::addRoute(std::string const& method, std::string const& pattern, Handler handler) {
    routes.push_back({method, pattern, handler});
}

/// @brief Handle a request
/// @param request Request
/// @return HttpResponse
HttpResponse Router::dispatch(HttpRequest const& request) const {
    for (const auto& route: routes) {
        if (route.method != request.method) continue;

        bool match = std::regex_search(request.path, route.pattern);

        if (match) return route.handler(request);
    }

    return HttpResponse("404 Not Found", HttpResponseHeader(), "");
}

