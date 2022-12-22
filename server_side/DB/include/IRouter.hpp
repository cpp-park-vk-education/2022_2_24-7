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
    virtual bool addHandler(const std::string& method, const Handler& handler) = 0;
    virtual bool processRoute(const Request& request, const ConnectionPtr& userConnection) = 0;
    virtual bool sendToUser(const Reply& reply, const ConnectionPtr& userConnection) = 0;
    virtual bool sendToAllProjectUsers(const Reply& reply, const ConnectionPtr& userConnection) = 0;
};
