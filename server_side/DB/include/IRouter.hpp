#pragma once

#include <string>
#include <unordered_map>

#include "IResponse.hpp"

class IRouter {
   public:
    virtual void addHandler(const std::string& method,
                            const Handler& handler) = 0;
    virtual Reply processRoute(const Request& request) = 0;

    virtual bool connectUser(const User& user) = 0;
    virtual bool disconnectUser(const User& user) = 0;

    virtual void sendToAllProjectUsers(const Reply& reply) = 0;
};

using Handler = Reply (*)(const IResponse& request, const std::string filePath);
