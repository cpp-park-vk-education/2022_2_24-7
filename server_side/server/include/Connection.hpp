#pragma once

#include "IConnection.hpp"
#include "IReply.hpp"
#include "IRequest.hpp"
#include "IRouter.hpp"
#include "ISerializer.hpp"

#include "boost/asio.hpp"
#include "boost/array.hpp"

class Connection : public IConnection
{
    void handle_read() override;
    void handle_write() override;

public:

    Connection(boost::asio::io_service& io_service, IRouter& router);
    void start() override;
    void get_socket() override;

private:

    boost::asio::ip::tcp::socket socket;
    boost::array<char, 8192> readBuf;
    boost::array<char, 8192> writeBuf;

    IRequest request;
    IReply reply;
    ISerializer serializer;
    IRouter& router;
};

//сделать ли сериалайзер тоже единственным, как и роутер
