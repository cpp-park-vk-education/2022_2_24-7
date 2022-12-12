#pragma once

#include <string>
#include <vector>

#include "IConnection.hpp"
#include "IWorkWithData.hpp"
#include "User.hpp"

class IProject {
    virtual bool connectUser() = 0;
    virtual bool disconnectUser() = 0;

    virtual const std::vector<User> getUsers() = 0;
};
