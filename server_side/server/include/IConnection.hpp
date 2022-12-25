#pragma once

#include <boost/asio.hpp>

#include "nlohmann/json.hpp"

class IConnection {
   public:
    virtual void run(size_t *all_connections_, size_t *closed_connections_) = 0;
    virtual boost::asio::ip::tcp::socket &getSocket() = 0;
    virtual void writeMsg(std::string msg) = 0;
};
