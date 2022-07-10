#ifndef _HTTP_SOCKET_
#define _HTTP_SOCKET_

#include <map>
#include <string>
#include <stdlib.h>

#include "../headers/utils.hpp"
#include "./socket.hpp"

using namespace std;

class HTTPSocket: public Socket {
    public:
        HTTPSocket(int socket_fd): Socket(socket_fd) {};

        void sendResponse(int code, string status_text);

        void setResponseBody(string body) {
            this -> response_body = body;
        }

        void setResponseHeaders(string key, string value) {
            this -> response_headers[key] = value;
        }

        map<string,string> getRequestHeaders(void);

        string getRequestBody(void);
        
    private:
        map<string,string> request_headers;
        map<string,string> response_headers;
        string request_body;
        string response_body;
};

#endif