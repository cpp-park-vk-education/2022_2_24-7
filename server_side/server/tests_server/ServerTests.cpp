#include <gtest/gtest.h>

#include "Server.hpp"
#include "Serializer.hpp"

TEST(ServerTest, StartServer) {
    IRouter router;
    Serializer serializer;
    
    Server server(serializer, router);
}
