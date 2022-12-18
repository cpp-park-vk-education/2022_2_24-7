#pragma once

#include <string>

struct IResponse {
    virtual char GetMethod() = 0;
};
