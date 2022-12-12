#pragma once

#include <string>
#include <unordered_map>

#include "IResponse.hpp"
#include "Reply.hpp"
#include "Request.hpp"
#include "User.hpp"

using Handler = Reply (*)(const IResponse& request, const std::string filePath);

class IRouter {
   public:
    virtual void addHandler(const std::string& method,
                            const Handler& handler) = 0;
    virtual Reply processRoute(const Request& request) = 0;

    // virtual bool connectUser(const User& user) = 0;
    // virtual bool disconnectUser(const User& user) = 0;

    virtual void sendToUser(const User& user) = 0;
    virtual void sendToAllProjectUsers(const Reply& reply) = 0;
};