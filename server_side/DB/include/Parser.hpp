#pragma once

#include "IParser.hpp"

class Parser : IParser {
   public:
    std::string parseRequestToString(const Request &request);
    Reply parseStringToReply(const std::string &strReply);
};
