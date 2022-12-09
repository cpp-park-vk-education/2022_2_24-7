#pragma once

#include <boost/shared_ptr.hpp>
#include <ISerializer.hpp>
class IConnection
{

public:

    virtual void handle_read() = 0;
    virtual void handle_write() = 0;
    virtual void start() = 0;
    virtual void get_socket() = 0;
};

using ConnectionPtr = boost::shared_ptr<IConnection>;
