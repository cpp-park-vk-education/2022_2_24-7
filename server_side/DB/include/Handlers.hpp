#pragma once

#include <string>

#include "IResponse.hpp"
#include "Reply.hpp"
#include "Request.hpp"

Reply InsertSymbol(IResponse& request, const std::string filePath);
Reply DeleteSymbol(IResponse& request, const std::string filePath);
