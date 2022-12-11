#pragma once
#include <vector>
#include <sstream>
#include <string>

#include "element.hpp"

std::vector<std::string> parseString(std::string str, char separator);

struct Command {
    Command(std::string str) {
        int x = 1;
        _insertElement = nullptr;
        _afterElemenet = nullptr;
        _beforeElement = nullptr;

        std::vector<std::string> parsedString = parseString(str, ':');

        char a = parsedString[parsedString.size() - 1][0];
        if (a == '1') {
            std::vector <std::string> beforeElementInStrings = parseString(parsedString[2], '|');

            size_t countBefore;
            size_t userBefore;
            
            countBefore = std::stoul(beforeElementInStrings[0]);
            userBefore = std::stoul(beforeElementInStrings[1]);

            char tmpSymbol = ' ';
            _beforeElement = new Element(&tmpSymbol, &countBefore, &userBefore);
        } else if (a == '2') {
            std::vector <std::string> afterElementInStrings = parseString(parsedString[2], '|');
            
            size_t countAfter;
            size_t userAfter;
            
            countAfter = std::stoul(afterElementInStrings[0]);
            userAfter = std::stoul(afterElementInStrings[1]);

            char tmpSymbol = ' ';
            _afterElemenet = new Element(&tmpSymbol, &countAfter, &userAfter);
        } else if (a == '3') {
            std::vector <std::string> afterElementInStrings = parseString(parsedString[2], '|');

            size_t countAfter;
            size_t userAfter;
            
            countAfter = std::stoul(afterElementInStrings[0]);
            userAfter = std::stoul(afterElementInStrings[1]);

            char tmpSymbol = ' ';
            _afterElemenet = new Element(&tmpSymbol, &countAfter, &userAfter);

            // before element
            std::vector <std::string> beforeElementInStrings = parseString(parsedString[3], '|');

            size_t countBefore;
            size_t userBefore;
            
            countBefore = std::stoul(beforeElementInStrings[0]);
            userBefore = std::stoul(beforeElementInStrings[1]);

            tmpSymbol = ' ';
            _beforeElement = new Element(&tmpSymbol, &countBefore, &userBefore);

            // insert element
        }
        std::vector<std::string> insertElementStrings = parseString(parsedString[1], '|');

        size_t countInsert;
        size_t userInsert;
        
        countInsert = std::stoul(insertElementStrings[0]);
        userInsert = std::stoul(insertElementStrings[1]);

        _insertElement = new Element(&insertElementStrings[2][0], &countInsert, &userInsert);
    }

    Element* _insertElement;
    Element* _afterElemenet;
    Element* _beforeElement;

    ~Command() {
        // ERROR may be error not init
        delete _afterElemenet;
        delete _beforeElement;
    }
};

