#pragma once

#include <string>

#include "IResponse.hpp"
#include <boost/serialization/access.hpp>

struct Reply : IResponse {
    private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive& ar, unsigned) {
        ar & command;
    }    
    
    public:
    char GetMethod() override { return command[0]; }

    Reply(std::string _command) : command(_command){};

    bool operator==(Reply repl) const { return (command == repl.command); }

    std::string GetCommand() override { return command; }

    std::string command;
};

