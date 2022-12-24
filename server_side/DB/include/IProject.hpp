#pragma once

#include <string>
#include <vector>

#include "../../server/include/IConnection.hpp"
#include "IWorkWithData.hpp"

using ConnectionPtr = IConnection*;

class IProject {
    virtual bool ConnectUser(const ConnectionPtr& userConnection) = 0;
    virtual bool DisconnectUser(const ConnectionPtr& userConnection) = 0;};
