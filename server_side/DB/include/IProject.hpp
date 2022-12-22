#pragma once

#include <string>
#include <vector>

#include "IConnection.hpp"
#include "IWorkWithData.hpp"

class IProject {
    virtual bool ConnectUser(const ConnectionPtr& userConnection) = 0;
    virtual bool DisconnectUser(const ConnectionPtr& userConnection) = 0;
};
