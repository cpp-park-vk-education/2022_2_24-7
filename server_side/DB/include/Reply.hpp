#pragma once

#include "IResponse.hpp"

struct Reply : IResponse {
    std::string GetMethod() override { return method; }

    Reply(std::string _method, std::string _countUser = "",
          std::string _userId = "", std::string _insertChar = "",
          std::string _afterChar = "", std::string _beforeChar = "",
          std::string _number = "")
        : method(_method),
          countUser(_countUser),
          userId(_userId),
          insertChar(_insertChar),
          afterChar(_afterChar),
          beforeChar(_beforeChar),
          number(_number){};

    std::string method;
    std::string countUser;   // количество изменений
    std::string userId;      // уникальный ID польователя
    std::string insertChar;  // символ для вноса
    std::string afterChar;  // элемент после символа для вноса
    std::string beforeChar;  // элемент до символа для вноса
    std::string number;      // режим для заноса символа
};
