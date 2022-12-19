#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "Handlers.hpp"
#include "IProject.hpp"
#include "IRouter.hpp"
#include "Project.hpp"
#include "Reply.hpp"
#include "Request.hpp"
#include "User.hpp"

using Handler = Reply (*)(IResponse& request, const std::string filePath);

class Router : public IRouter {
   public:
    Router();

    bool addHandler(const std::string& method,
                    const Handler& handler) override{};

    bool processRoute(Request& request,
                      const ConnectionPtr& userConnection) override {
        addHandler("i", InsertSymbol);
        return true;
    };



    const Project GetProject() const { return project; };
    const std::unordered_map<std::string, Handler> GetHandlers() const {
        return handlersMap;
    };

    bool sendToAllProjectUsers(const Reply& reply,
                               const ConnectionPtr& userConnection) override;
    bool sendToUser(const Reply& reply,
                    const ConnectionPtr& userConnection) override;

   private:
    std::unordered_map<std::string, Handler> handlersMap;
    Project project;
};
