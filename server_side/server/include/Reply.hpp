#pragma once

#include <boost/serialization/access.hpp>
#include <string>
struct Reply {
   private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& ar, unsigned) {
        ar& command;
    }

   public:
    std::string command;
};
