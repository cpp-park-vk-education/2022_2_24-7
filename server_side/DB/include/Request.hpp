#pragma once

#include "IResponse.hpp"

struct Request : IResponse {
    char GetMethod() override { return command[0]; }

    Request(std::string __string) : command(__string) {};

    std::string command;
};
