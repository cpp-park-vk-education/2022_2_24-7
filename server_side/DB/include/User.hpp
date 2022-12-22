#pragma once

#include <boost/shared_ptr.hpp>
#include <string>

#include "IConnection.hpp"

struct User {
    User(int _userID, ConnectionPtr _newConnection = nullptr,
         int _countUser = 1)
        : userID(_userID),
          userConnection(_newConnection),
          countUserChanges(_countUser){};

    int userID;
    ConnectionPtr userConnection;  //ссылка на соединение с пользователем
    int countUserChanges;  //количество изменений, сделанных пользователем
};
