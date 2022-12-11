#pragma once

#include "IResponse.hpp"

struct Request : IResponse {

    std::string GetMethod() override {
        return method;
    }

    std::string method;
    std::string countUser; // количество изменений
    std::string userId; // уникальный ID польователя
    std::string insertChar; // символ для вноса
    std::string afterChar;  // элемент после символа для вноса
    std::string beforeChar; // элемент до символа для вноса
    std::string nember; // режим для заноса символа
};
