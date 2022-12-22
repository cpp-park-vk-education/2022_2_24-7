#pragma once

#include "Dto.hpp"
#include "IConnection.hpp"

class Router {
   public:
    void processRoute(const Dto& request, const IConnection& connect) { }
};
