#pragma once

#include "IResponse.hpp"

struct Request : IResponse {
    char GetMethod() override { return command[0]; }

    Request(std::string __string) : command(__string) {};

    bool operator==(Request req) const {
        return (command == req.command);
    }

    std::string command;
};
