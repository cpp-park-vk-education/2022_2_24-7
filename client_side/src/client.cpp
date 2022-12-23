#include "client.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>

// std::mutex m;

Client::Client(boost::asio::io_context& context, std::string ip, unsigned int port) :
    _inputStream(context, STDIN_FILENO), _socket(context), _ip(ip), _port(port) {
        connect();
    }

void Client::sendData() {
    // std::lock_guard<std::mutex> lk(m);

    nlohmann::json j;
    j["command"] = dto.command;

    std::cout << j.dump() << std::endl;
    _socket.send(boost::asio::buffer(j.dump()));
}

void Client::getData() {
    // std::lock_guard<std::mutex> lk(m);

    std::cout << "----- INPUT BEFORE RECEIVING -----" << std::endl;

    boost::asio::streambuf b;
    boost::asio::read_until(_socket, b, '}');
    std::istream is(&b);
    std::string input;
    std::copy(std::istreambuf_iterator<char>(is),
        std::istreambuf_iterator<char>(),
        std::back_inserter(input));

    std::cout << "----- INPUT AFTER RECEIVING -----" << std::endl;
    std::cout << "INPUT LENGTH = " << input.length() << std::endl;
    std::cout << input << std::endl;
    std::cout << "----- END OF INPUT -----" << std::endl;

    nlohmann::json j = nlohmann::json::parse(input);

    std::string command;
    command = j["command"];

    // SOME LOGIC
}

void Client::setDto(std::string command) {
    dto.command = command;
}

void Client::connect() {
    if (_socket.is_open()) {
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        _socket.close();
    }
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(_ip), _port);

    _socket.connect(ep);
    // std::async(std::launch::async, std::bind(&Client::getData, Client(_socket, _ip, _port)));
}

void Client::stopConnection() {
    _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);

    _inputStream.close(); 
    _socket.close();

    std::cout << "CONNECTION IS CLOSED" << std::endl;
}
