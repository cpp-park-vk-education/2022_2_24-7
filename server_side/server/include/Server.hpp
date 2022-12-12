#pragma once

#include <boost/asio.hpp>
#include <vector>

#include "IConnection.hpp"
#include "IServer.hpp"
#include "ServerConfig.hpp"

class Server : public IServer {
    void start_accept() override;
    void handle_accept(const boost::system::error_code& e) override;
    void handle_stop() override;

   public:
    Server(ISerializer& ser, IRouter& router);
    void run() override;

   private:
    boost::asio::io_service service;
    boost::asio::signal_set signals;
    boost::asio::ip::tcp::acceptor acceptor;

    ISerializer& serializer;
    IRouter& router;
    ServerConfig config;
    ConnectionPtr newConnection;
    std::vector<ConnectionPtr> connections;
};
