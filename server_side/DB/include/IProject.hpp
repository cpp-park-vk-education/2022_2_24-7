#pragma once

#include <string>
#include <vector>

#include "IConnection.hpp"
#include "IWorkWithData.hpp"
#include "User.hpp"

class IProject {
    virtual bool ConnectUser(const ConnectionPtr& userConnection) = 0;
    virtual bool DisconnectUser(const ConnectionPtr& userConnection) = 0;

    virtual std::vector<User> GetUsers() const = 0;
};
