#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#include "./headers/server.hpp"
#include "./headers/router.hpp"

int example_callback(int socket) {
    std::cout << "Example callback called..." << std::endl;
    return 1;
}

int main()
{
    // Router* router = new Router();
    // router->addRoute("POST","/", example_callback);


    Server *server = new Server(8082);
    server->serve();
    return 0;
}