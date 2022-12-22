#include "Router.hpp"

Router::Router(std::string filesPath)
    : project(Project("project", filesPath)), workWithData() {
    workWithData = new WorkWithData;
};

bool Router::sendToUser(const Reply& reply,
                        const ConnectionPtr& userConnection) {
    userConnection->handle_write();

    return true;
};

bool Router::sendToAllProjectUsers(const Reply& reply,
                                   const ConnectionPtr& userConnection) {
    /*    if (project.GetUsers().size() == 0) {
            return 0;
        }
        for (int i = 0; i < project.GetUsers().size(); ++i) {
            if (project.GetUsers()[i].userConnection != userConnection) {
                sendToUser(reply, project.GetUsers()[i].userConnection);
            }
        }
        */
    return true;
};

void Router::processRoute(Request& request,
                          const ConnectionPtr& userConnection) {
    std::string replyCommand = request.command;
    workWithData->operationWithData(request.command, true);
    Reply reply(replyCommand);
    sendToAllProjectUsers(reply, userConnection);
};

const Project Router::GetProject() const { return project; };

const IWorkWithData* Router::GetWorkWithData() const { return workWithData; };
