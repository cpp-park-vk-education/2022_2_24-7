#pragma once

#include "Reply.hpp"
#include "Request.hpp"
#include "IResponse.hpp"

Reply InsertSymbol(const Request& request);
Reply DeleteSymbol(const Reply& request);
Reply GetProjectFile(const Reply& request);
