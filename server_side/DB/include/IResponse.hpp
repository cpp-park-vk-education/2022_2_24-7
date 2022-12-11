#pragma once

#include <string>

struct IResponse {
    virtual std::string GetMethod() = 0;
};
