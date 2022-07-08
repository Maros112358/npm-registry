#ifndef _ROUTER_
#define _ROUTER_

#include <map>
#include <string>

typedef int (*RouteCallback)(int);

using namespace std;

class Router {
    public:
        Router(void) {
        }

        void addRoute(string route, RouteCallback callback) {
            this->routes[route] = callback;
        }

        RouteCallback getRoute(string route) {
            return this->routes[route];
        }
    private:
        map <string, RouteCallback> routes;
};

#endif