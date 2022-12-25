#include "Server.hpp"

#include <iostream>

#include "Connection.hpp"

Server::Server(boost::asio::io_context &context, IRouter &router, unsigned int port)
    : io_context_(context),
      acceptor_(context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      _router(router) {}

void Server::start() { acceptConnection(); }

void Server::acceptConnection() {
    std::shared_ptr<Connection> connection = Connection::create(io_context_, _router);
    acceptor_.async_accept(connection->getSocket(), boost::bind(&Server::handleConnection, this, connection,
                                                                boost::asio::placeholders::error));
}

void Server::handleConnection(std::shared_ptr<Connection> newConnection,
                              const boost::system::error_code &error) {
    if (error) {
        std::cerr << "CONNECTION ERROR " << error.message() << "\n";
        acceptConnection();
        return;
    }
    std::cout << "CLIENT CONNECTED\n";
    ++all_connections_;
    std::cout << "CONNECTIONS : " << all_connections_ - closed_connections_ << std::endl;
    newConnection->run(&all_connections_, &closed_connections_);  // RUN
    acceptConnection();
}
