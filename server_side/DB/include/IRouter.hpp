#pragma once

#include <string>

#include "IResponse.hpp"
#include "Reply.hpp"
#include "Request.hpp"

using Handler = Reply (*)(const IResponse& request);

class IRouter {
   public:
    virtual void addHandler(const std::string& method,
                            const Handler& handler) = 0;
    virtual Reply processRoute(const IResponse& request) = 0;
};
