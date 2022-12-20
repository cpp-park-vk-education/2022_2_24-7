#pragma once

#include "IProject.hpp"
#include "IWorkWithData.hpp"
#include "User.hpp"

class Project : IProject {
   public:
    Project(std::string newFilesPath = "./files",
            std::string newProjectName = "project")
        : filesPath(newFilesPath),
          projectName(newProjectName),
          projectUsers(),
          userIdCounter(0){};

    bool ConnectUser(const ConnectionPtr& userConnection) override;
    bool DisconnectUser(const ConnectionPtr& userConnection) override;

    std::vector<User> GetUsers() const override;

    const std::string GetPath() const;

    const std::string GetName() const;

    int GetCounter() const;

    User FindUser(const ConnectionPtr& userConnection);
    bool UserExist(const ConnectionPtr& userConnection);
    
    // IWorkWithData &WorkWithData;
   private:
    std::string filesPath;
    std::string projectName;
    std::vector<User> projectUsers;
    int userIdCounter;
};
