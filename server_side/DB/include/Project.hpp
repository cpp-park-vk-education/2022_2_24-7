#pragma once

#include <limits>
#include <string>
#include <vector>
#include <unordered_map>

#include "IConnection.hpp"
#include "IProject.hpp"
#include "IWorkWithData.hpp"


//using ConnectionPtr = std::make_shared<IConnection> (Connection());

class Project : IProject {
   public:
    Project(std::string newProjectName = "project",
            std::string newFilesPath = "./files");

    bool ConnectUser(const ConnectionPtr& userConnection) override;
    bool DisconnectUser(const ConnectionPtr& userConnection) override;

    const std::string GetPath() const;
    const std::string GetName() const;
    const std::unordered_map<int, ConnectionPtr> GetProjectConnections() const;
    const int GetCounter() const;

    bool ConnectionExist(const ConnectionPtr& userConnection);
    int FindConnectionId(const ConnectionPtr& userConnection);

   private:
    std::string projectName;
    std::string filesPath;
    std::unordered_map<int, ConnectionPtr> projectConnections;
    int connectionIdCounter;
};
