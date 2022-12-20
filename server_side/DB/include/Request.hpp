#pragma once

#include <string>

#include "IResponse.hpp"
#include <boost/serialization/access.hpp>

struct Request : IResponse {
    private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& ar, unsigned) {
        ar & command;
    }    
    
    public:
    char GetMethod() override { return command[0]; }

    Request(std::string _command) : command(_command){};

    bool operator==(Request req) const { return (command == req.command); }

    std::string GetCommand() override { return command; }

    std::string command;
};
