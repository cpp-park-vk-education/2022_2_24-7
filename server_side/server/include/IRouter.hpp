#pragma once

#include "Reply.hpp"
#include "Request.hpp"
#include "IConnection.hpp"

class IRouter {
   public:
    Reply processRoute(const Request& request, const IConnection& connect) { }
};
