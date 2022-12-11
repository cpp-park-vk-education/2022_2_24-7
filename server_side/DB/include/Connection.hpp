#pragma once

#include "IConnection.hpp"
#include "IRouter.hpp"
#include "ISerializer.hpp"
#include "Reply.hpp"
#include "Request.hpp"
#include "boost/asio.hpp"

class Connection : public IConnection {
    void handle_read() override;
    void handle_write() override;

   public:
    Connection(boost::asio::io_service& io_service, ISerializer& serializer,
               IRouter& router);
    void start() override;
    void get_socket() override;

   private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf readBuf;
    boost::asio::streambuf writeBuf;

    Request request;
    Reply reply;
    ISerializer& serializer;
    IRouter& router;
};
