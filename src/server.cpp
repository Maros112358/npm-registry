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

#include "./headers/server.hpp"
#include "./headers/socket.hpp"
#include "./headers/utils.hpp"
#include "./headers/http_socket.hpp"

using namespace std;

int Server::serve() {
    struct sockaddr_in server_addr;
    cout << "Server triggered with port " << port << endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY); // localhost
    server_addr.sin_port = htons(port); // port

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
        cout << "Incoming request..." << endl;
        if (client_socket < 0) {
            cout << "=> Error on accepting..." << endl;
        }

        HTTPSocket *socket = new HTTPSocket(client_socket);
        // vector<string> http_parts = split(socket -> getLine(), " ");
        map<string,string> headers = socket -> getHeaders();
        auto iter = headers.begin();
        while (iter != headers.end()) {
            cout << "[" << iter->first << ","
                        << iter->second << "]\n";
            ++iter;
        }
        cout << endl;

        // string curr_line;
        // while (curr_line != "\r") {
        //     cout << curr_line << endl;
        //     curr_line = socket -> getLine();
        // }
        // cout << "===End of header===" << endl;

        close(client_socket);
    }

    close(server_socket);
    return 0;
}
