#pragma once

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <memory>
#include <string>

#include "Handler.hpp"
#include "IConnection.hpp"

static inline constexpr int BUFF_SIZE = 512;

class Connection : public IConnection, public std::enable_shared_from_this<Connection> {
   public:
    Connection(boost::asio::io_context &io_context_);

    void run(size_t *id) override;

    boost::asio::ip::tcp::socket &getSocket() override;

    std::shared_ptr<Connection> getPtr() { return shared_from_this(); }

    static std::shared_ptr<Connection> create(boost::asio::io_context &io_context_) {
        return std::make_shared<Connection>(io_context_);
    }

   private:
    Handler handler;

    char read_buff[BUFF_SIZE];
    std::string write_buff;
    boost::asio::ip::tcp::socket socket_;

    size_t *connections_ = nullptr;
    size_t id_;

    void readMsg();

    void handleRead(const boost::system::error_code &error, size_t bytes);

    std::string handleMsg(std::string Msg);

    void sendReply();

    void closeConnection();

    void dummy(const boost::system::error_code &error, size_t bytes) {}
};
