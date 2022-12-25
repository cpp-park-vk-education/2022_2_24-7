#pragma once

#include <nlohmann/json.hpp>
#include <string>

class IHandler {
   public:
    virtual void handleFromClient(std::string msg) = 0;
    virtual void handleFromBack(std::string msg) = 0;
    virtual nlohmann::json reply() = 0;
};
