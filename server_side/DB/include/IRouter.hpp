#pragma once

#include <string>
#include <unordered_map>

#include "IProject.hpp"
#include "IResponse.hpp"
#include "Reply.hpp"
#include "Request.hpp"

class IRouter {
   public:
    virtual void processRoute(const std::string& request, const ConnectionPtr userConnection) = 0;
    virtual bool sendToUser(const Reply& reply, const ConnectionPtr userConnection) = 0;
    virtual bool sendToAllProjectUsers(const Reply& reply, const ConnectionPtr userConnection) = 0;
};
