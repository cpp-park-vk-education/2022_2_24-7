#include "Handlers.hpp"

Reply InsertSymbol(IResponse& request, const std::string filePath) {
    Reply reply("1");
    reply.command = request.GetCommand();
    // Process request and crete reply
    return reply;
};

Reply DeleteSymbol(IResponse& request, const std::string filePath) {
    Reply reply("1");
    reply.command = request.GetCommand();
    // Process request and crete reply
    return reply;
};
