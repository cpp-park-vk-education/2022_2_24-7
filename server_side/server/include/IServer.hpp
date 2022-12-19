#pragma once

#include "IRouter.hpp"
#include "ISerializer.hpp"

class IServer {
   public:
    virtual void start_accept() = 0;
    virtual void handle_accept(const boost::system::error_code& e) = 0;
    virtual void handle_stop() = 0;
    virtual void run() = 0;
};
