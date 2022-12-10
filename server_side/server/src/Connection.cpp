#include "Connection.hpp"
#include "IRouter.hpp"

void Connection::handle_read() {}

void Connection::handle_write() {}

Connection::Connection(boost::asio::io_service& io_service, ISerializer& serializer, IRouter& router)
    : socket(io_service), serializer(serializer), router(router) {}

void Connection::start() {}

void Connection::get_socket() {}
