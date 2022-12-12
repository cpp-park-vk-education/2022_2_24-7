#pragma once

#include "IProject.hpp"
#include "IWorkWithData.hpp"
#include "User.hpp"

class Project : IProject {
   public:
    Project();

    bool connectUser();
    bool disconnectUser();

    const std::vector<User> getUsers() override;

   private:
    std::string projectName;
    std::string projectFilePath;

    IWorkWithData &WorkWithData;

    ConnectionPtr newConnection;
    std::vector<User> Users;
};
