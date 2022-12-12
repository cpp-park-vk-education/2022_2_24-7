#include <gtest/gtest.h>

#include "Serializer.hpp"
#include "Server.hpp"

TEST(ServerTest, StartServer) {
    IRouter router;
    Serializer serializer;

    Server server(serializer, router);
}
