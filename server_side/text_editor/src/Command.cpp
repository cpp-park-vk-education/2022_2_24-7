#include "Command.hpp"

#include <iostream>

std::vector<std::string> parseString(std::string str, char separator) {
        std::vector <std::string> parseString;
        return parseString;
}

Command::Command(std::string str) {
}

Command::~Command() {
    if (_beforeElement) {
        delete _beforeElement;
    }
    if (_afterElemenet) {
        delete _afterElemenet;
    }
}
