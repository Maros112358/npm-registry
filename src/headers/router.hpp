#ifndef _ROUTER_
#define _ROUTER_

#include <map>
#include <string>

#include "../sockets/http_socket.hpp"

typedef int (*RouteCallback)(HTTPSocket*);

using namespace std;

class Router {
    public:
        Router(RouteCallback fallback) {
            this -> fallback = fallback;
        }

        void addRoute(string route, RouteCallback callback) {
            this->routes[route] = callback;
        }

        RouteCallback getCallback(string route) {
            if (routes.count(route)) {
                return this -> routes[route];
            }

            return this -> fallback;
        }
    private:
        map <string, RouteCallback> routes;
        RouteCallback fallback;
};

#endif