#include "Router.hpp"

Router::Router(IWorkWithData* _workWithData, std::string filesPath)
    : project(Project("project", filesPath)), workWithData(_workWithData){};

bool Router::sendToUser(const Reply& reply, const ConnectionPtr userConnection) {
    std::string tempMsg = reply.command;
    userConnection->writeMsg(tempMsg);
    return true;
};

bool Router::sendToAllProjectUsers(const Reply& reply, const ConnectionPtr userConnection) {
    if (project.GetProjectConnections().size() == 0) {
        return false;
    }
    int u = project.FindConnectionId(userConnection);
    std::unordered_map<int, ConnectionPtr> tempProjectConnections = project.GetProjectConnections();
    for (auto& i : tempProjectConnections) {

        if (i.first != u) {
            sendToUser(reply, i.second);
        }
    }
    return true;
};

void Router::processRoute(const std::string& request, const ConnectionPtr userConnection) {

    std::string replyCommand = request;
    // workWithData->operationWithData(replyCommand, true);
    Reply reply(request);
    sendToAllProjectUsers(reply, userConnection);
};

Project* Router::GetProject() { return &project; };

IWorkWithData* Router::GetWorkWithData() const { return workWithData; };


bool Router::disconnectProjectUser(const ConnectionPtr userConnection) {
    project.DisconnectUser(userConnection);
    return true;
};

bool Router::connectProjectUser(const ConnectionPtr userConnection) {
    project.ConnectUser(userConnection);
    return true;
}
