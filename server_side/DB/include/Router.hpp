#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "../../server/include/IConnection.hpp"
#include "IProject.hpp"
#include "IRouter.hpp"
#include "IWorkWithData.hpp"
#include "Project.hpp"
#include "Reply.hpp"
#include "Request.hpp"

class Router : public IRouter {
   public:
    Router(std::string filesPath = "./files");

    ~Router() { delete workWithData; }

    void processRoute(const std::string& request, const ConnectionPtr userConnection) override;

    bool sendToAllProjectUsers(const Reply& reply, const ConnectionPtr& userConnection) override;
    bool sendToUser(const Reply& reply, const ConnectionPtr& userConnection) override;

    Project* GetProject();
    IWorkWithData* GetWorkWithData() const;

   private:
    Project project;
    IWorkWithData* workWithData;
};
