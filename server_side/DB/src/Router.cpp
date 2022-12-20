#include "Router.hpp"
#include "IWorkWithData.hpp"
#include <iostream>








Router::Router(std::string filesPath) : project(Project(filesPath)){
    addHandler("i", InsertSymbol);
    addHandler("d", DeleteSymbol);
    workWithData = new WorkWithData;

};

bool Router::sendToUser(const Reply& reply,
                        const ConnectionPtr& userConnection) {
    userConnection->handle_write();

    return 1;
};

bool Router::sendToAllProjectUsers(const Reply& reply,
                                   const ConnectionPtr& userConnection) {
    if (project.GetUsers().size() == 0) {
        return 0;
    }
    for (int i = 0; i < project.GetUsers().size(); ++i) {
        if (project.GetUsers()[i].userConnection != userConnection) {
            sendToUser(reply, project.GetUsers()[i].userConnection);
        }
    }

    return 1;
};

bool Router::processRoute(Request& request,
                      const ConnectionPtr& userConnection) {
        char method = request.GetMethod();
        handlersMap.at(method)(request, project.GetPath());
        std::string replyCommand;
        replyCommand = workWithData->operationWithData(request.command, true);
        Reply reply(replyCommand);
        sendToAllProjectUsers(reply, userConnection);
        return true;
};
