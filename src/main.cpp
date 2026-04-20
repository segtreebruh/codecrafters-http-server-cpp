#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

struct HTTPRequest {
  std::string req;
  std::string headers;
  std::string body;
  
  HTTPRequest() {}
  HTTPRequest(std::string req, std::string headers, std::string body)
    : req(req), headers(headers), body(body) {}

  HTTPRequest(const std::string& request) {
    size_t reqEndPos = request.find("\r\n");
    // header end marked with extra \r\n
    size_t headersEndPos = request.find("\r\n\r\n");

    // if fail: return nothing
    if (reqEndPos == std::string::npos || headersEndPos == std::string::npos) return;

    req = request.substr(0, reqEndPos);
    headers = request.substr(reqEndPos + 2, headersEndPos - (reqEndPos + 2));
    body = request.substr(headersEndPos + 4);
  }

  // don't really need friend since everything public 
  // but still write friend to remember syntax
  friend std::ostream& operator<<(std::ostream& os, const HTTPRequest& request) {
    os << "--REQ--\n" << request.req << "\n"
          << "--HEADERS--\n" << request.headers << "\n"
          << "--BODY--\n" << request.body << "\n";
    return os;
  }
};

int main(int argc, char **argv) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  
  // You can use print statements as follows for debugging, they'll be visible when running tests.
  std::cout << "Logs from your program will appear here!\n";

  // TODO: Uncomment the code below to pass the first stage
  
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
  
  if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
    std::cerr << "Failed to bind to port 4221\n";
    return 1;
  }
  
  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
    std::cerr << "listen failed\n";
    return 1;
  }
  
  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);
  
  std::cout << "Waiting for a client to connect...\n";
  
  int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
  std::cout << "Client connected\n";

  /*
    Instead of using buffer (very low-level, error prone, mental math heavy), 
    I tried to use string for easier handling
  */
  // char buffer[1024] = {0};
  // recv(client_fd, buffer, sizeof(buffer), 0);
  std::string rawRequest(1024, '\0');
  // ssize_t: size_t but signed (so, can be -1)
  ssize_t n = recv(client_fd, rawRequest.data(), rawRequest.size(), 0);
  // resize to delete all trailing '\0'
  // size_t: UNSIGNED. so check if n invalid first 
  if (n > 0) rawRequest.resize(static_cast<size_t>(n));

  for (size_t i = 0; i < rawRequest.size(); i++) {
    if (rawRequest[i] == '\r') std::cout << "\\r";

    // prefer using "\n" 
    // "\n" do not flush output buffer
    // while endl: basically cout << "\n" then std::flush(), flush output buffer after
    // expensive operation, much slower
    else if (rawRequest[i] == '\n') std::cout << "\\n";
    else std::cout << rawRequest[i];
  }
  std::cout << "\n";

  HTTPRequest request = HTTPRequest(rawRequest);
  std::cout << request << '\n';

  std::string const response200 = "HTTP/1.1 200 OK\r\n\r\n";
  std::string const response404 = "HTTP/1.1 404 Not Found\r\n\r\n";
  std::string echoResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n";
  std::string contentLength = "Content-Length: ";
  
  // send(client_fd, response, strlen(response), 0);

  if (request.req.find("GET / ") != std::string::npos) { 
    send(client_fd, response200.data(), response200.size(), 0);
    std::cout << "OK";
  }
  else if (request.req.find("GET /echo/") != std::string::npos) {
    int echo = request.req.find("/echo") + 6;
    int http = request.req.find("HTTP") - 1;
    std::string content = request.req.substr(echo, http - echo);
    echoResponse += contentLength + std::to_string(static_cast<int>(content.size())) + "\r\n\r\n";
    echoResponse += content;
    std::cout << echoResponse << "\n";
    send(client_fd, echoResponse.data(), echoResponse.size(), 0);
  }
  else {
    send(client_fd, response404.data(), response404.size(), 0);
    std::cout << "404";
  }
  std::cout << "\n";
  
  close(client_fd);
  close(server_fd);

  return 0;
}
