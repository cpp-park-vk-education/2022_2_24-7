#include "Parser.hpp"

std::string Parser::parseRequestToString(const Request &request) {
    std::string tmp;
    tmp = request.method;
    return tmp;
}
Reply Parser::parseStringToReply(const std::string &strReply) {
    Reply tmp("1");
    tmp = strReply;
    return tmp;
}
