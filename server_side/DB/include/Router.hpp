#pragma once

#include <string>
#include "Reply.hpp"
#include "Request.hpp"
#include "IResponse.hpp"
#include "IRouter.hpp"
#include <unordered_map>
#include "Handlers.hpp"

template<typename Handler>
class Router : public IRouter {
    public:
    
    Router() {
        addHandler("i", InsertSymbol);
        addHandler("d", DeleteSymbol);
    }
    
    void addHandler(const std::string &method, const Handler &handler) {
        handlersMap.emplace(method, handler)
    }



    Reply process_route(const std::string &method, const IResponse& request) {
        if(auto handler_it = handlersMap.find(method); handler_it != handlersMap.end()) {
            return (handler_it->second)(request)
        }
        Reply failReply;

        return failReply;
    }


    private:
    std::unordered_map<std::string, Handler> handlersMap; 
};
// в объявлении на серваке это выглядит как-то так:
Router<Reply(*)(const Request &request)> myRouter;