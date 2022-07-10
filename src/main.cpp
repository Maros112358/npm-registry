#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

#include "./headers/server.hpp"
#include "./headers/router.hpp"
#include "./sockets/http_socket.hpp"

int example_callback(HTTPSocket *socket) {
    ifstream t("./src/html/index.html");
    stringstream buffer;
    buffer << t.rdbuf();
    t.close();
    socket -> setResponseBody(buffer.str());
    socket -> setResponseHeaders("Content-Type", "text/html; charset=utf-8");
    socket -> sendResponse(200, "OK");  
    return 1;
}

int fallback_callback(HTTPSocket *socket) {
    ifstream t("./src/html/404.html");
    stringstream buffer;
    buffer << t.rdbuf();
    t.close();
    socket -> setResponseBody(buffer.str());
    socket -> setResponseHeaders("Content-Type", "text/html; charset=utf-8");
    socket -> sendResponse(404, "Not found");  
    return 1;
}

int main()
{
    Router* router = new Router(fallback_callback);
    router->addRoute("/", example_callback);


    Server *server = new Server(8085, router);
    server->serve();
    return 0;
}