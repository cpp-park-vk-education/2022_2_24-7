#include "Router.hpp"

Router::Router(IParser &_parser, std::vector<ConnectionPtr> &_connections, std::vector<User> &_users,
           std::string _filesPath = "./")
    : parser(_parser), connections(_connections), projectUsers(_users), filesPath(_filesPath) {
    addHandler("i", InsertSymbol);
    addHandler("d", DeleteSymbol);
};

void Router::addHandler(const std::string &method, const Handler &handler) {
    handlersMap.emplace(method, handler);
};

Reply Router::processRoute(const Request &request) {
        std::string method = request.method;
        if (auto handler_it = handlersMap.find(method);
            handler_it != handlersMap.end()) {
            return (handler_it->second)(request, filesPath);
        };
        Reply failReply("FAIL");
        return failReply;
};

void Router::sendToAllProjectUsers(const Reply &reply) {
    std::string msg;
    



};