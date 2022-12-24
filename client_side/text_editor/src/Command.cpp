#include "Command.hpp"
// #include "../include/Command.hpp"

#include <iostream>

std::vector<std::string> parseString(std::string str, char separator) {
        std::vector <std::string> parseString;
        
        std::stringstream stream(str);
        std::string segmentOfStream;

        while (std::getline(stream,segmentOfStream, separator)) {
            parseString.push_back(segmentOfStream);
        }

        return parseString;
};

Command::Command(std::string str) {
        _insertElement = nullptr;
        _afterElemenet = nullptr;
        _beforeElement = nullptr;

        std::vector<std::string> parsedString = parseString(str, ':');

        if (parsedString[0][0] == 'i') {
            // insert command
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
                
                _beforeElement = new Element(&tmpSymbol, &countAfter, &userAfter);

                // before element
                std::vector <std::string> beforeElementInStrings = parseString(parsedString[3], '|');

                size_t countBefore;
                size_t userBefore;
                
                countBefore = std::stoul(beforeElementInStrings[0]);
                userBefore = std::stoul(beforeElementInStrings[1]);

                tmpSymbol = ' ';

                _afterElemenet = new Element(&tmpSymbol, &countBefore, &userBefore);

                // insert element
            }
            std::vector<std::string> insertElementStrings = parseString(parsedString[1], '|');

            size_t countInsert;
            size_t userInsert;
            
            countInsert = std::stoul(insertElementStrings[0]);
            userInsert = std::stoul(insertElementStrings[1]);

            _insertElement = new Element(&insertElementStrings[2][0], &countInsert, &userInsert);

            Element* tmp = _afterElemenet;
            _afterElemenet = _beforeElement;
            _beforeElement = tmp;
        } else {
            // delete command
            std::vector<std::string> insertElementStrings = parseString(parsedString[1], '|');

            size_t countInsert;
            size_t userInsert;
            
            countInsert = std::stoul(insertElementStrings[0]);
            userInsert = std::stoul(insertElementStrings[1]);
            char a = ' ';
            _insertElement = new Element(&a, &countInsert, &userInsert);
        }
}
    
Command::~Command() {
    if (_beforeElement) {
    delete _beforeElement;
    }
    if(_afterElemenet) {   
        delete _afterElemenet;
    }
};
