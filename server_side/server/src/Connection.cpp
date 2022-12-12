#include "Connection.hpp"

#include <boost/bind/bind.hpp>

void Connection::handle_read(const boost::system::error_code& e) {
    if (!e) {
        Request request;
        serializer.save(readBuf, request);

        Reply reply = router.processRoute(request);

        serializer.load(writeBuf, reply);

        boost::asio::async_write(
            socket, writeBuf,
            boost::bind(&IConnection::handle_write, shared_from_this(), boost::asio::placeholders::error));
    }
}

void Connection::handle_write(const boost::system::error_code& e) {
    if (!e) {
        boost::asio::async_read(
            socket, readBuf,
            boost::bind(&IConnection::handle_read, shared_from_this(), boost::asio::placeholders::error));
    }
}

Connection::Connection(boost::asio::io_service& io_service, ISerializer& serializer, IRouter& router)
    : socket(io_service), serializer(serializer), router(router) {}

void Connection::start() {
    boost::asio::async_read(
        socket, readBuf,
        boost::bind(&IConnection::handle_read, shared_from_this(), boost::asio::placeholders::error));
}

boost::asio::ip::tcp::socket& Connection::get_socket() { return socket; }
