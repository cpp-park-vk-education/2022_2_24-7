#pragma once

#include "IProject.hpp"
#include "IWorkWithData.hpp"
#include "User.hpp"

class Project : IProject {
   public:
    Project(std::string newProjectName = "project", std::string newFilesPath = "./files")
        : projectName(newProjectName), filesPath(newFilesPath), projectUsers(), userIdCounter(0){};

    bool ConnectUser(const ConnectionPtr& userConnection) override { return true; };
    bool DisconnectUser(const ConnectionPtr& userConnection) override { return true; };

    std::vector<User> GetUsers() const override { return projectUsers; };

    const std::string GetPath() const { return filesPath; };

    const std::string GetName() const { return projectName; }

    const int GetCounter() const { return userIdCounter; }
    // IWorkWithData &WorkWithData;
   private:
    std::string projectName;
    std::string filesPath;
    std::vector<User> projectUsers;
    int userIdCounter;
};
