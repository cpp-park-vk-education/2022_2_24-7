#pragma once

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/asio.hpp>

#include "Reply.hpp"
#include "Request.hpp"

class ISerializer {
   public:
    virtual void save(boost::asio::streambuf& writeBuf, Request& req) = 0;
    virtual void load(boost::asio::streambuf& readBuf, Reply& rep) = 0;
};
