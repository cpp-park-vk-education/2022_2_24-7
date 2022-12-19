#pragma once

#include <string>

struct IResponse {
    virtual char GetMethod() = 0;
    virtual std::string GetCommand() = 0;
};
