#include "Connection.hpp"

#include <boost/bind/bind.hpp>

void Connection::handle_read(const boost::system::error_code& e) { }

void Connection::handle_write(const boost::system::error_code& e) { }

Connection::Connection(boost::asio::io_service& io_service, ISerializer& serializer, IRouter& router)
    : socket(io_service), serializer(serializer), router(router) { }

void Connection::start() {}

boost::asio::ip::tcp::socket& Connection::get_socket() { }
