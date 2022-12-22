#pragma once

#include <boost/asio.hpp>

class IConnection {
   public:
    virtual void run(size_t *id) = 0;
    virtual boost::asio::ip::tcp::socket &getSocket() = 0;
};
