#ifndef _SERVER_
#define _SERVER_

class Server {
    public:
        Server(int port) {
            this->port = port;
            std::cout << "Initialized server with port " << this->port << std::endl;
        }
        int serve();
        int port;
};

#endif