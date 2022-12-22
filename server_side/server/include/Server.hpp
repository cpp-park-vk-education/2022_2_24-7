#pragma once

#include "Connection.hpp"
#include "IServer.hpp"

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/system.hpp>

#include <memory>
#include <vector>

static inline constexpr int default_port = 2020;

class Server : public IServer {
   public:
    Server(boost::asio::io_context &context, unsigned int port = default_port);
    void start() override;   

   private:
    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    size_t connections_ = 0;

    void acceptConnection();
    void handleConnection(std::shared_ptr <Connection> newConnection,
                              const boost::system::error_code &error);
};
