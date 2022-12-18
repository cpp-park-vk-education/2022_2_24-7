#pragma once

#include "IResponse.hpp"

struct Reply : IResponse {
  char GetMethod() override { return command[0]; }

  Reply(std::string __string) : command(__string)  {};

  bool operator==(Reply repl) const {
        return (command == repl.command);
  }

  std::string command;
};
