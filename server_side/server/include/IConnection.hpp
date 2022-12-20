#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

class IConnection : public boost::enable_shared_from_this<IConnection> {
   public:
    virtual void handle_read(const boost::system::error_code& e) = 0;
    virtual void handle_write(const boost::system::error_code& e) = 0;
    virtual void start() = 0;
    virtual boost::asio::ip::tcp::socket& get_socket() = 0;
};

using ConnectionPtr = boost::shared_ptr<IConnection>;
