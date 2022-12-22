#include "Project.hpp"

Project::Project(std::string newProjectName, std::string newFilesPath)
    : projectName(newProjectName), filesPath(newFilesPath), projectConnections(), connectionIdCounter(0){};

bool Project::ConnectUser(const ConnectionPtr& userConnection) {
    if (ConnectionExist(userConnection) == true) {
        return false;
    }
    projectConnections.emplace(connectionIdCounter, userConnection);
    connectionIdCounter = (connectionIdCounter + 1) % std::numeric_limits<int>::max();
    return true;
};

bool Project::DisconnectUser(const ConnectionPtr& userConnection) {
    int tempConnectionId = FindConnectionId(userConnection);
    if (tempConnectionId == -1) {
        return false;
    }
    projectConnections.erase(tempConnectionId);
    return true;
};

const std::string Project::GetPath() const { return filesPath; };

const std::string Project::GetName() const { return projectName; }

const std::unordered_map<int, ConnectionPtr> Project::GetProjectConnections() const {
    return projectConnections;
};

const int Project::GetCounter() const { return connectionIdCounter; }

bool Project::ConnectionExist(const ConnectionPtr& userConnection) {
    for (auto& i : projectConnections) {
        if (i.second == userConnection) {
            return true;
        }
    }
    return false;
};

int Project::FindConnectionId(const ConnectionPtr& userConnection) {
    for (auto& i : projectConnections) {
        if (i.second == userConnection) {
            return i.first;
        }
    }
    return -1;
};
