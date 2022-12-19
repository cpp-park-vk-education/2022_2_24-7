#pragma once

#include "IProject.hpp"
#include "IWorkWithData.hpp"
#include "User.hpp"

class Project : IProject {
   public:
    Project(std::string newProjectName = "project",
            std::string newFilesPath = "./files")
        : projectName(newProjectName),
          filesPath(newFilesPath),
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
    std::string projectName;
    std::string filesPath;
    std::vector<User> projectUsers;
    int userIdCounter;
};
