#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <nlohmann/json.hpp>
#include <boost/system.hpp>
#include <thread>

#include <memory>
#include <string>
#include <vector>

static inline constexpr int BUFF_SIZE = 512;

class Client : public std::enable_shared_from_this<Client> {
   public:
    Client(boost::asio::io_context& context, std::string ip = "127.0.0.1", short unsigned int port = 2020);
    void start();

    void sendMsg(std::string msg);
    void closeConnection();

   private:
    boost::asio::ip::tcp::socket _socket;

    std::string _ip;
    short unsigned int _port;

    boost::asio::streambuf read_buff;
    std::string write_buff;
    nlohmann::json dto;

    void acceptConnection();

    void readMsg();
    void handleRead(const boost::system::error_code &error, size_t bytes);
    std::string handleMsg(std::string msg);
    void dummy(const boost::system::error_code &error, size_t bytes);
};
