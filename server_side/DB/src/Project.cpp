#include "Project.hpp"

User Project::FindUser(const ConnectionPtr& userConnection) {
    for (auto usr : projectUsers) {
        if (userConnection == usr.userConnection) {
            return usr;
        }
    }
    User tmpUsr(-1);
    return tmpUsr;
};

bool Project::UserExist(const ConnectionPtr& userConnection) {
    for (auto usr : projectUsers) {
        if (userConnection == usr.userConnection) {
            return true;
        }
    }
    return false;
};

std::vector<User> Project::GetUsers() const { return projectUsers; };

const std::string Project::GetPath() const { return filesPath; };

const std::string Project::GetName() const { return projectName; }

int Project::GetCounter() const { return connectionIdCounter; }

bool Project::ConnectUser(const ConnectionPtr& userConnection) {
    User tempUser(connectionIdCounter, userConnection, 1);
    connectionIdCounter += 1;
    projectUsers.push_back(tempUser);
    return true;
};

bool Project::DisconnectUser(const ConnectionPtr& userConnection) {
    if (projectUsers.size() == 0) {
        return 0;
    }
    for (int i = 0; i < projectUsers.size(); ++i) {
        if (projectUsers[i].userConnection == userConnection) {
            projectUsers.erase(projectUsers.begin() + i);
            return true;
        }
    }
    return false;
};
