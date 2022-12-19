#pragma once
#include <vector>
#include <sstream>
#include <string>

#include "element.hpp"

std::vector<std::string> parseString(std::string str, char separator);

struct Command {
    Command(std::string str);

    Element* _insertElement;
    Element* _afterElemenet;
    Element* _beforeElement;

    ~Command();
};

