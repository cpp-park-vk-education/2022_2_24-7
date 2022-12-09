#pragma once

#include "IReply.hpp"
#include "IRequest.hpp"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/access.hpp>

class ISerializer 
{

public:

    friend class boost::serialization::access;

    template<class Archive> 
    void serialize(Archive& archive, IRequest& req, const unsigned int version)
    {

    }

    template<class Archive> 
    void serialize(Archive& archive, IReply& req, const unsigned int version)
    {

    }

    template<class Archive> 
    void serialize(Archive& archive, boost::array<char, 8192> buf, const unsigned int version)
    {

    }
    
    virtual void save();
    virtual void load();
};
