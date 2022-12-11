#pragma once

#include <string>

#include "IConnection.hpp"

struct User {
    User(std::string _userID, ConnectionPtr _newConnection, int _countUser = 0)
        : userID(_userID),
          userConnection(_newConnection),
          countUserChanges(_countUser){};

    std::string userID;
    ConnectionPtr userConnection;
    int countUserChanges;  //количество изменений
};
