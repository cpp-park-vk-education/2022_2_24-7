#pragma once

#include "IConnection.hpp"
#include "IRouter.hpp"
#include "ISerializer.hpp"
#include "Reply.hpp"
#include "Request.hpp"

class Connection : public IConnection {
    void handle_read(const boost::system::error_code& e) override;
    void handle_write(const boost::system::error_code& e) override;

   public:
    Connection(boost::asio::io_service& io_service, ISerializer& serializer, IRouter& router);
    void start() override;
    boost::asio::ip::tcp::socket& get_socket() override;

   private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf readBuf;
    boost::asio::streambuf writeBuf;

    ISerializer& serializer;
    IRouter& router;
};
