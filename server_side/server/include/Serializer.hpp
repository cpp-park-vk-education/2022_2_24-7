#pragma once

#include "ISerializer.hpp"

class Serializer : public ISerializer {
   public:
    void save(boost::asio::streambuf& writeBuf, Request& req) override;
    void load(boost::asio::streambuf& readBuf, Reply& rep) override;
};
