#include <iostream>

#include "IRouter.hpp"
#include "Serializer.hpp"
#include "Server.hpp"

int main() {
    Serializer serializer;
    IRouter router;
    Server server(serializer, router);

    server.run();

    return 0;
}
