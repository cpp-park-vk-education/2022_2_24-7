#include "Router.hpp"
#include "IParser.hpp"

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

void Router::sendToAllProjectUsers(const Reply &reply) { std::string msg; };

void Router::getPrivat() {
    Request req("hqllo");
    std::cout << std::endl;
    std::cout << "parser = " << parser.parseRequestToString(req) << std::endl;
    std::cout << "connections size = " << connections.size() << std::endl;
    std::cout << "projectUsers size = " << projectUsers.size() << std::endl;
    std::cout << "handlersMap size = " << handlersMap.size() << std::endl;
    std::cout << "filesPath = " << filesPath << std::endl;
    std::cout << "usersCount = " << usersCount << std::endl;
    std::cout << std::endl;
}

void Router::sendToUser(const User &user) {
    std::cout << "\n HELLO USER \n";
};
