#include "Router.hpp"

Router::Router(std::string filesPath) : project(Project("project", filesPath)), workWithData() {
    workWithData = new WorkWithData;
};

bool Router::sendToUser(const Reply& reply, const ConnectionPtr& userConnection) { // здесь передается dto, а не реплай
    // userConnection->writeMsg();

    return true;
};

bool Router::sendToAllProjectUsers(const Reply& reply, const ConnectionPtr& userConnection) {
    if (project.GetProjectConnections().size() == 0) {
        return false;
    }
    std::unordered_map<int, ConnectionPtr> tempProjectConnections = project.GetProjectConnections();
    for (auto& i : tempProjectConnections) {
        if (i.second == nullptr) {  // если пользователь отключился, то я удаляю конекшн из списка
            project.DisconnectUser(i.second);
            continue;
        }
        if (i.second != userConnection) {
            sendToUser(reply, i.second);
        }
    }
    return true;
};

void Router::processRoute(const std::string& request, const ConnectionPtr userConnection) {
    std::string replyCommand = request;
    workWithData->operationWithData(replyCommand, true);
    Reply reply(replyCommand);
    sendToAllProjectUsers(reply, userConnection);
};

Project* Router::GetProject() { return &project; };

IWorkWithData* Router::GetWorkWithData() const { return workWithData; };
