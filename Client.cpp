#include "Client.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>

#define IO_BIND(a)                                                                    \
    boost::bind(&Client::a, shared_from_this(), boost::asio::placeholders::error, \
                boost::asio::placeholders::bytes_transferred)

Client::Client(boost::asio::io_context& context, std::string ip, short unsigned int port) :
    _socket(context), _ip(ip), _port(port) {}

void Client::start() { acceptConnection(); }

void Client::acceptConnection() {
    if (_socket.is_open()) {
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        _socket.close();
    }
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(_ip), _port);
    
    _socket.connect(ep);

    readMsg();
}

void Client::sendMsg(std::string msg) {
    nlohmann::json j;
    j["command"] = msg;

    std::cout << j.dump() << std::endl;
    _socket.send(boost::asio::buffer(j.dump()));
}

void Client::readMsg() {
    std::cout << "----- INPUT BEFORE RECEIVING -----" << std::endl;

    boost::asio::async_read_until(_socket, read_buff, '}', IO_BIND(handleRead));
}

void Client::handleRead(const boost::system::error_code &error, size_t bytes) {
    if (error) {
        switch (error.value()) {
            case boost::asio::error::eof:  // ?
                closeConnection();
                break;
            default:
                std::cerr << ": INPUT READ ERROR: " << error.message() << "\n";
                break;
        }
        return;
    }
    if (bytes == 0) {
        std::cerr << ": NO INPUT GOT\n";
        return;
    }

    std::istream is(&read_buff);
    std::string msg;
    std::copy(std::istreambuf_iterator<char>(is),
        std::istreambuf_iterator<char>(),
        std::back_inserter(msg));

    handleMsg(msg);  // BLOCKING OPERATION
    readMsg();
}

void Client::handleMsg(std::string msg) {
    std::cout << "SERVER MESSAGE : " << msg << std::endl;
    
//    _f(msg);
    _window->serverAsked(msg);
}

void Client::closeConnection() {
    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

    _socket.close();

    std::cout << "CONNECTION IS CLOSED" << std::endl;
}

void Client::addClass(IMainWindow* wind) {
    _window = wind;
}

//void Client::addFunc(void (*f)(std::string)) {
//    _f = f;
//}
