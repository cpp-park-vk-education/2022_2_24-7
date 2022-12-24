#include "Connection.hpp"

#include <iostream>

#define IO_BIND(a)                                                                    \
    boost::bind(&Connection::a, shared_from_this(), boost::asio::placeholders::error, \
                boost::asio::placeholders::bytes_transferred)

Connection::Connection(boost::asio::io_context &io_context_, IRouter& router) : handler(), socket_(io_context_), _router(router) {}

void Connection::run(size_t *all_connections, size_t *closed_connections) {
    id_ = *all_connections;
    all_connections_ = all_connections;
    closed_connections_ = closed_connections;
    nlohmann::json j;
    j["command"] = "First message from server";
    j["id"] = id_;
    socket_.write_some(boost::asio::buffer(j.dump()));
    readMsg();
}

boost::asio::ip::tcp::socket &Connection::getSocket() { return socket_; }

void Connection::readMsg() {
    std::fill(read_buff, read_buff + BUFF_SIZE, 0);
    socket_.async_read_some(boost::asio::buffer(read_buff, BUFF_SIZE), IO_BIND(handleRead));
}

void Connection::handleRead(const boost::system::error_code &error, size_t bytes) {
    if (error) {
        switch (error.value()) {
            case boost::asio::error::eof:
                closeConnection();
                break;
            default:
                std::cerr << id_ << ": INPUT READ ERROR: " << error.message() << "\n";
                break;
        }
        return;
    }
    if (bytes == 0) {
        std::cerr << id_ << ": NO INPUT GOT\n";
        return;
    }

    handleMsg(std::string(read_buff, bytes));  // BLOCKING OPERATION
    readMsg();
}

void Connection::handleMsg(std::string Msg) {
    std::cout << "CLIENT MESSAGE : " << Msg << std::endl;
    handler.handleFromClient(Msg);  
    _router.processRoute(handler.reply()["command"], this);// BLOCKING OPERATION
}

void Connection::writeMsg(std::string msg) {
    handler.handleFromBack(msg);
    write_buff = handler.reply().dump();
    async_write(socket_, boost::asio::buffer(write_buff), IO_BIND(dummy));
    write_buff.clear();
}

void Connection::closeConnection() {
    std::cout << "CLIENT HAS EXITED\n";
    ++(*closed_connections_);
    all_connections_ = nullptr;
    closed_connections_ = nullptr;
    socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket_.close();
}
