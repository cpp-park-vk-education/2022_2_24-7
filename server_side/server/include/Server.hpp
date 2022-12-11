#pragma once

#include <boost/asio.hpp>
#include <vector>

#include "IConnection.hpp"
#include "IRouter.hpp"
#include "IServer.hpp"
#include "ServerConfig.hpp"

class Server : public IServer {
    void start_accept() override;
    void handle_accept() override;
    void stop_accept() override;

   public:
    Server();

   private:
    boost::asio::io_service service;
    boost::asio::signal_set signals;
    boost::asio::ip::tcp::acceptor acceptor;

    ServerConfig config;
    ConnectionPtr newConnection;
    std::vector<ConnectionPtr> connections;
};
