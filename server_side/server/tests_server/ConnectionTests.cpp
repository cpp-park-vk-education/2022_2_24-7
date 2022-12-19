#include <gtest/gtest.h>

#include "Connection.hpp"
#include "Serializer.hpp"

TEST(ConnectionTest, StartConnection) {
    boost::asio::io_service service;
    IRouter router;
    Serializer serializer;
    
    ConnectionPtr connect;
    connect.reset(new Connection(service, serializer,  router));
    connect->start();
}
