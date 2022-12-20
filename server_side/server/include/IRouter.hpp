#pragma once

#include "Reply.hpp"
#include "Request.hpp"

class IRouter {
   public:
    Reply processRoute(const Request& request) {
        Reply rep { request.command };
        return rep;
    }
};
