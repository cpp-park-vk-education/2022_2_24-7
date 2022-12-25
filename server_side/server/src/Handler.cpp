#include "Handler.hpp"

void Handler::handleFromClient(std::string msg) { convertMsgToDto(msg); }

void Handler::handleFromBack(std::string msg) { convertDtoToMsg(msg); }

nlohmann::json Handler::reply() {
    auto return_dto = dto;
    dto.clear();
    return return_dto;
}

void Handler::convertMsgToDto(std::string msg) { dto = nlohmann::json::parse(msg); }

void Handler::convertDtoToMsg(std::string msg) { dto["command"] = msg; }
