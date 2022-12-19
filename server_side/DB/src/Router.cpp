#include "Router.hpp"

#include <iostream>

Router::Router() {
    project = Project();
    addHandler("i", InsertSymbol);
    addHandler("d", DeleteSymbol);
};

bool Router::sendToUser(const Reply& reply,
                        const ConnectionPtr& userConnection) {
    userConnection->handle_write();

    return 1;
};

bool Router::sendToAllProjectUsers(const Reply& reply,
                                   const ConnectionPtr& userConnection) {
    return 1;
};

bool Router::createProject(std::string _filesPath) { return 0; };
