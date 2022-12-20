#pragma once

#include "IResponse.hpp"

struct Request : IResponse {
    char GetMethod() override { return command[0]; }

    Request(std::string _command) : command(_command){};

    bool operator==(Request req) const { return (command == req.command); }

    std::string GetCommand() override { return command; }

    std::string command;
};
