#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include "Handlers.hpp"
#include "IRouter.hpp"

#include "Parser.hpp"
#include "Reply.hpp"
#include "Request.hpp"
#include "User.hpp"

using Handler = Reply (*)(const IResponse& request, const std::string filePath);

class Router : public IRouter {
   public:
    Router(Parser &_parser, std::vector<ConnectionPtr> &_connections,
           std::vector<User> &_users, std::string _filesPath = "./")
    : parser(_parser),
      connections(_connections),
      projectUsers(_users),
      filesPath(_filesPath) {
    usersCount = 0;
    addHandler("i", InsertSymbol);
    addHandler("d", DeleteSymbol);
};

    void addHandler(const std::string& method,
                            const Handler& handler) override;

    Reply processRoute(const Request &request) override;

    void sendToAllProjectUsers(const Reply &reply) override;

    void sendToUser(const User &user);
    // bool connectUser(const User &user) override;
    // bool disconnectUser(const User &user) override;
    void getPrivat();
   private:
    Parser &parser;
    std::vector<ConnectionPtr> &connections;
    std::vector<User> &projectUsers;
    std::unordered_map<std::string, Handler> handlersMap;
    std::string filesPath;
    int usersCount;
};
