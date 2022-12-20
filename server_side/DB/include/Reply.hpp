#pragma once

#include "IResponse.hpp"

struct Reply : IResponse {
    char GetMethod() override { return command[0]; }

    Reply(std::string _command) : command(_command){};

    bool operator==(Reply repl) const { return (command == repl.command); }

    std::string GetCommand() override { return command; }

    std::string command;
};
