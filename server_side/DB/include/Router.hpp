#pragma once

#include <string>
#include <unordered_map>

#include "Handlers.hpp"
#include "IRouter.hpp"
#include "Parser.hpp"
#include "Reply.hpp"
#include "Request.hpp"
#include "User.hpp"

class Router : public IRouter {
   public:
    Router(IParser &_parser, std::vector<ConnectionPtr> &_connections, std::vector<User> &_users,
           std::string _filesPath = "./");

    void addHandler(const std::string &method, const Handler &handler) override;

    Reply processRoute(const Request &request) override;

    void sendToAllProjectUsers(const Reply &reply) override;

    // bool connectUser(const User &user) override;
    // bool disconnectUser(const User &user) override;
   private:
    IParser &parser;
    std::vector<ConnectionPtr> &connections;
    std::vector<User> &projectUsers;
    std::unordered_map<std::string, Handler> handlersMap;
    std::string filesPath;
};
