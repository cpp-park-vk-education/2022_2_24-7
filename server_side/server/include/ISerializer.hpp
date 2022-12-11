#pragma once

#include <boost/asio.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/access.hpp>

#include "Reply.hpp"
#include "Request.hpp"

class ISerializer {
   public:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& archive, Request& req, const unsigned int version) {}

    template <class Archive>
    void serialize(Archive& archive, Reply& req, const unsigned int version) {}

    template <class Archive>
    void serialize(Archive& archive, boost::asio::streambuf buf, const unsigned int version) {}

    virtual void save() = 0;
    virtual void load() = 0;
};
