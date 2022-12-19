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

int Project::GetCounter() const { return userIdCounter; }

std::vector<User> Project::GetUsers() const { return projectUsers; };

const std::string Project::GetPath() const { return filesPath; };

const std::string Project::GetName() const { return projectName; }

bool Project::ConnectUser(const ConnectionPtr& userConnection) {
    User tempUser(userIdCounter, userConnection, 1);
    userIdCounter += 1;
    projectUsers.push_back(tempUser);
    return true;
};

bool Project::DisconnectUser(const ConnectionPtr& userConnection) {
    for (auto i = projectUsers.begin(); i != projectUsers.end(); ++i) {
        if (i->userConnection == userConnection) {
            projectUsers.erase(i);
            return true;
        }
    }

    return false;
};
