#pragma once

#include <string>
#include "Reply.hpp"
#include "Request.hpp"
#include "IResponse.hpp"

template<typename Handler>
class IRouter {
    public:
    virtual void addHandler(const std::string &method, const Handler &handler) = 0;
    virtual Reply processRoute(const IResponse& request) = 0;
};
