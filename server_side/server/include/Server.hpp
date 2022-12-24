#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/system.hpp>
#include <memory>
#include <vector>

#include "Connection.hpp"
#include "IServer.hpp"
#include "../../DB/include/IRouter.hpp"

static inline constexpr int default_port = 2020;

class Server : public IServer {
   public:
    Server(boost::asio::io_context &context, IRouter& router, unsigned int port = default_port);
    void start() override;

   private:
    boost::asio::io_context &io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    size_t all_connections_ = 0;
    size_t closed_connections_ = 0;
    IRouter& _router;

    void acceptConnection();
    void handleConnection(std::shared_ptr<Connection> newConnection, const boost::system::error_code &error);
};
