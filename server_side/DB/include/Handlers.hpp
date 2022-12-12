#pragma once

#include <string>

#include "IResponse.hpp"
#include "Reply.hpp"
#include "Request.hpp"

Reply InsertSymbol(const IResponse& request, const std::string filePath);
Reply DeleteSymbol(const IResponse& request, const std::string filePath);
