#pragma once

#include "IParser.hpp"
#include "Request.hpp"
#include "Reply.hpp"
#include <string>

class Parser : IParser {
   public:
    std::string parseRequestToString(const Request &request) override;
    Reply parseStringToReply(const std::string &strReply) override;
};
