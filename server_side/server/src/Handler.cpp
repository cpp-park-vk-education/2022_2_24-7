#include "Handler.hpp"

#include <iostream>

void Handler::handle(std::string msgBuffer) {
    inputAnalyze(msgBuffer);
}

void Handler::handle(const Dto& msgBack) {
    inputAnalyze(msgBack);
}

std::string Handler::reply() {
    return reply_;
}

void Handler::inputAnalyze(std::string msgBuffer) {
    convertMsgToDto(msgBuffer);
}

void Handler::inputAnalyze(const Dto& msgBack) {
    convertDtoToMsg(msgBack);
}

void Handler::logic() { }

void Handler::convertMsgToDto(std::string vpnMsg) {
    nlohmann::json j = nlohmann::json::parse(vpnMsg);
    dto.command = j["command"].get<std::string>();
}

void Handler::convertDtoToMsg(const Dto&) {
    reply_ = dto.command;
}
