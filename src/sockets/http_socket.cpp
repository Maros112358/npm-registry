#include "./http_socket.hpp"

map<string,string> HTTPSocket::getRequestHeaders(void) {
            if (!(this -> request_headers.empty())) {
                return this -> request_headers;
            }

            vector<string> parts;
            string curr_line;

            curr_line = this -> getLine();
            parts = split(curr_line, " ");
            this -> request_headers["Method"] = parts.at(0);
            this -> request_headers["URL"] = parts.at(1);
            this -> request_headers["Protocol"] = parts.at(2);

            
            // rest of headers
            curr_line = this -> getLine();
            while (curr_line != "\r") {
                curr_line.pop_back();

                parts = split(curr_line, " ");
                parts.at(0).pop_back();
                this -> request_headers[parts.at(0)] = parts.at(1);

                curr_line = this -> getLine();
            }

            return this -> request_headers;
}

string HTTPSocket::getRequestBody(void) {
            int content_length;

            if (this -> request_body.size()) {
                return this -> request_body;
            }

            if (this -> request_headers.empty()) {
                getRequestHeaders();
            }

            if (!(this -> request_headers.count("Content-Length"))) {
                return "";
            }

            // TODO: Check if value for "Content-Length" is numerical
            content_length = stoi(this -> request_headers["Content-Length"]);

            this -> request_body = this -> getChars(content_length);
            return this -> request_body;
}

void HTTPSocket::sendResponse(int code, string status_text) {
            string res = "HTTP/1.1 " + to_string(code) + " " + status_text + "\r\n";
            
            for ( const pair<string, string> &p : this -> response_headers) {
                res += p.first + ": " + p.second + "\r\n"; 
            } 
            
            res += "Content-Length: " + to_string(this -> response_body.size()) + "\r\n\r\n";
            res += response_body;
            send(this -> getSocket(), res.c_str(), res.size(), 0);
}