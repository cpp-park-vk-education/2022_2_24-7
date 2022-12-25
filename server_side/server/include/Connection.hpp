#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <memory>
#include <string>

#include "../../DB/include/IRouter.hpp"
#include "Handler.hpp"
#include "IConnection.hpp"

static inline constexpr int BUFF_SIZE = 512;

class Connection : public IConnection, public std::enable_shared_from_this<Connection> {
   public:
    Connection(boost::asio::io_context &io_context_, IRouter &router);

    void run(size_t *all_connections_, size_t *closed_connections_) override;

    boost::asio::ip::tcp::socket &getSocket() override;

    void writeMsg(std::string msg) override;

    std::shared_ptr<Connection> getPtr() { return shared_from_this(); }

    static std::shared_ptr<Connection> create(boost::asio::io_context &io_context_, IRouter &router) {
        return std::make_shared<Connection>(io_context_, router);
    }

   private:
    Handler handler;
    IRouter &_router;

    char read_buff[BUFF_SIZE];
    std::string write_buff;
    boost::asio::ip::tcp::socket socket_;

    size_t *all_connections_ = nullptr;
    size_t *closed_connections_ = nullptr;
    size_t id_;

    void readMsg();

    void handleRead(const boost::system::error_code &error, size_t bytes);

    void handleMsg(std::string Msg);

    void closeConnection();

    void dummy(const boost::system::error_code &error, size_t bytes) {}
};
