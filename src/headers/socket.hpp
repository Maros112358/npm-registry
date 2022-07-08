#ifndef _ROUTER_
#define _ROUTER_

#include <sys/socket.h>
#include <map>
#include <string>

using namespace std;

class Socket {
    public:
        Socket(int socket_fd) {
            this -> socket_fd = socket_fd;
        }

        char getChar(void) {
            char readChar[1];
            recv(this->socket_fd, &readChar, sizeof(readChar), 0);
            return readChar[0];
        }

        string getLine(void) {
            string r = "";
            char c;

            c = this -> getChar();
            while ((c != '\n')) {
                r.push_back(c);
                c = this -> getChar();
            }

            return r;
        }
    private:
        int socket_fd;
};

#endif