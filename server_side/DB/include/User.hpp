#pragma once

#include <boost/shared_ptr.hpp>
#include <string>

#include "IConnection.hpp"
using ConnectionPtr = boost::shared_ptr<IConnection>;

struct User {
    User(int _userID, ConnectionPtr _newConnection = nullptr,
          int _countUser = 1)
        : userID(_userID),
          userConnection(_newConnection),
          countUserChanges(_countUser) {};

    int userID;
    const ConnectionPtr& userConnection; //указатель на соединение с пользователем
    int countUserChanges;  //количество изменений, сделанных пользователем
};
