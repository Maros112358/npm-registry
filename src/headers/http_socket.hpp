#ifndef _HTTP_SOCKET__
#define _HTTP_SOCKET__

#include <map>
#include <string>

#include "./utils.hpp"
#include "./socket.hpp"

using namespace std;

class HTTPSocket: public Socket {
    using Socket::Socket;
    public:
        map<string,string> getHeaders(void) {
            map<string,string> header;
            vector<string> parts;
            
            string curr_line = this -> getLine();
            while (curr_line != "\r") {
                curr_line = curr_line.substr(0,curr_line.size()-2);
                parts = split(curr_line, " ");
                cout << parts.at(0) << " : " << parts.at(1) << endl; 
                header[parts.at(0)] = parts.at(1);
                curr_line = this -> getLine();
            }

            return header;
        }
};

#endif