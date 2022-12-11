#pragma once

#include "IResponse.hpp"
#include "Reply.hpp"
#include "Request.hpp"

Reply InsertSymbol(const IResponse& request);
Reply DeleteSymbol(const IResponse& request);
Reply GetProjectFile(const IResponse& request);
