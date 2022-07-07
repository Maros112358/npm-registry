#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
    int portNum = 1500;
    int bufsize = 1024;

    struct sockaddr_in server_addr;
    socklen_t size;

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {
        cout << "\nError establishing socket..." << endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(portNum);

    if ((bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr))) < 0) 
    {
        cout << "=> Error binding connection, the socket has already been established..." << endl;
        return 1;
    }

    int client_count = 1;
    listen(server_socket, client_count);
    cout << "=> Listening on port " << portNum << "..." << endl;

    int client_socket;
    size = sizeof(server_addr);
    char test_string[] = "ahoj";
    char request[1024];
    while (true) {
        client_socket = accept(server_socket, (struct sockaddr *) &server_addr, &size);
        recv(client_socket, request, sizeof(request), 0);
        cout << "=> Incoming request: " << request << endl;
        if (client_socket < 0) {
            cout << "=> Error on accepting..." << endl;
        }

        send(client_socket, &test_string, sizeof(test_string), 0);
        close(client_socket);
    }

    close(server_socket);
    return 0;
}