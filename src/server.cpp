#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


#include "./headers/server.hpp"
#include "./headers/router.hpp"

using namespace std;

int Server::serve() {
    struct sockaddr_in server_addr;
    cout << "Server triggered with port " << port << endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY); 
    server_addr.sin_port = htons(port);

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_socket < 0) {
        cout << "\nError establishing socket..." << endl;
        return -1;
    }

    if ((bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr))) < 0) 
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return -1;
    }

    int client_count =  1;
    listen(server_socket, client_count);
    cout << "=> Listening on port " << port << "..." << endl;

    int client_socket;
    socklen_t size = sizeof(server_addr);

    while (true) {
        client_socket = accept(server_socket, (struct sockaddr *) &server_addr, &size);
        cout << "Incoming request: ";
        if (client_socket < 0) {
            cout << "=> Error on accepting..." << endl;
        }

        HTTPSocket *socket = new HTTPSocket(client_socket);
        map<string,string> headers = socket -> getRequestHeaders();
        string URL = headers["URL"];
        string method = headers["Method"];
        cout << method << " " << URL << endl;

        RouteCallback callback = this -> router -> getCallback(URL);
        callback(socket);
        
        cout << "Closing socket..." << endl;
        close(client_socket);
    }

    close(server_socket);
    return 0;
}
