#pragma once

#include <string>
#include "Reply.hpp"
#include "Request.hpp"

template<typename Handler>
class IRouter {
    public:
    virtual void addHandler(const std::string &method, const Handler &handler) = 0;
    virtual Reply process_route(const std::string &method, const Request& request) = 0;
};
