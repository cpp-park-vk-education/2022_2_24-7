#include "Server.hpp"
#include "Connection.hpp"

#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>

void Server::start_accept() { }

void Server::handle_accept(const boost::system::error_code& e) { }

void Server::handle_stop() { service.stop(); }

Server::Server(ISerializer& ser, IRouter& router)
    : signals(service),
      acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001)),
      serializer(ser),
      router(router) { }

void Server::run() { }