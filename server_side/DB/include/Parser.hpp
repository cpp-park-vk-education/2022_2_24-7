#pragma once

#include <string>

#include "IParser.hpp"
#include "Reply.hpp"
#include "Request.hpp"

class Parser : IParser {
   public:
    std::string parseRequestToString(const Request &request) override;
    Reply parseStringToReply(const std::string &strReply) override;
};
