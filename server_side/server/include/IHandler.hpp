#pragma once

#include <string>

class IHandler {
public:
    virtual void handle(std::string ) = 0;
    virtual void handle(const Dto& ) = 0;
    virtual std::string reply() = 0;
};