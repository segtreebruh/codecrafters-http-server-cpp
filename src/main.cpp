#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include "controller.hpp"
#include "httpRequest.hpp"
#include "httpResponse.hpp"
#include "router.hpp"

// manual dependency injection
static Router buildRouter(std::string const& directory = "") {
    Router router;
    router.addRoute("GET", "^/$", indexHandler);
    router.addRoute("GET", "^/echo/", echoHandler);
    router.addRoute("GET", "^/user-agent$", userAgentHandler);

    FileController fileController(directory);
    router.addRoute("GET", "^/files/", [fileController](HttpRequest const& req) {
        return fileController.get(req);
    });
    router.addRoute("POST", "^/files/", [fileController](HttpRequest const& req) {
        return fileController.post(req);
    });

    return router;
}

void handleClientRequest(int client_fd, const Router& router) {
    std::cout << "Client connected\n\n";

    while (true) {
        std::string rawRequest(1024, '\0');
        ssize_t n = recv(client_fd, rawRequest.data(), rawRequest.size(), 0);
        if (n <= 0) break; // recv error - break
        rawRequest.resize(static_cast<size_t>(n));

        HttpRequest request(rawRequest);
        std::cout << request.str() << std::endl;
        HttpResponse response = router.dispatch(request);

        send(client_fd, response.str().data(), response.str().size(), 0);
        std::cout << response.str() << "\n";
    }

    close(client_fd);
}

int main(int argc, char** argv) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cout << "Logs from your program will appear here!\n";
    
    std::string directory;
    if (argc == 3) {
        if (std::string(argv[1]) == "--directory") directory = argv[2];
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Failed to create server socket\n";
        return 1;
    }

    // Since the tester restarts your program quite often, setting SO_REUSEADDR
    // ensures that we don't run into 'Address already in use' errors
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        std::cerr << "setsockopt failed\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(4221);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        std::cerr << "Failed to bind to port 4221\n";
        return 1;
    }

    int connection_backlog = 5;
    if (listen(server_fd, connection_backlog) != 0) {
        std::cerr << "listen failed\n";
        return 1;
    }

    Router router = buildRouter(directory);

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        std::cout << "Waiting for a client to connect...\n";

        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            std::cerr << "accept failed\n";
            continue;
        }

        std::thread([client_fd, &router]() {
            handleClientRequest(client_fd, router);
        }).detach();
    }

    close(server_fd);

    return 0;
}