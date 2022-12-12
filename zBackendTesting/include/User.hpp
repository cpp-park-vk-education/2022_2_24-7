#pragma once

#include <boost/shared_ptr.hpp>
#include <string>

#include "IConnection.hpp"
using ConnectionPtr = boost::shared_ptr<IConnection>;

struct User {
    User(std::string _userID, int _countUser = 0,
         ConnectionPtr _newConnection = nullptr)
        : userID(_userID),
          userConnection(_newConnection),
          countUserChanges(_countUser){};

    std::string userID;
    int countUserChanges;  //количество изменений
    ConnectionPtr userConnection;
};
