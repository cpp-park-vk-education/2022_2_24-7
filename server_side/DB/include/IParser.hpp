#pragma once

#include <string>

#include "Reply.hpp"
#include "Request.hpp"

class IParser {
   public:
    virtual std::string parseRequestToString(const Request &request) = 0;
    virtual Reply parseStringToReply(const std::string &strReply) = 0;
};
