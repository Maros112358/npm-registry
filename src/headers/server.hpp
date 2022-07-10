#ifndef _SERVER_
#define _SERVER_

#include "./router.hpp"

class Server {
    public:
        Server(int port, Router *router) {
            this -> port = port;
            this -> router = router;
            std::cout << "Initialized server with port " << this->port << std::endl;
        }
        int serve();
        int port;
    private:
        Router *router;
};

#endif