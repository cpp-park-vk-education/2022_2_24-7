#pragma once
#include <vector>
#include <sstream>
#include <string>

#include "element.hpp"

std::vector<std::string> parseString(std::string str, char separator) {
        std::vector <std::string> parseString;
        
        std::stringstream stream(str);
        std::string segmentOfStream;

        while (std::getline(stream,segmentOfStream, separator)) {
            parseString.push_back(segmentOfStream);
        }

        return parseString;
};

struct Command {
    Command(std::string str) {
        _insertElement = nullptr;
        _afterElemenet = nullptr;
        _beforeElement = nullptr;

        std::vector<std::string> parsedString = parseString(str, ':');

        char a = parsedString[parsedString.size()][0];
        if (a == '1') {
            std::vector <std::string> beforeElementInStrings = parseString(parsedString[2], '|');
            std::stringstream countBeforeStream(beforeElementInStrings[0]); 
            size_t countBefore;
            size_t userBefore;
            
            countBeforeStream >> countBefore;
            countBeforeStream << beforeElementInStrings[1];
            countBeforeStream >> userBefore;

            char tmpSymbol = ' ';
            _beforeElement = new Element(&tmpSymbol, &countBefore, &userBefore);
        } else if (a == '2') {
            std::vector <std::string> afterElementInStrings = parseString(parsedString[2], '|');
            std::stringstream countAfterStream(afterElementInStrings[0]); 
            size_t countAfter;
            size_t userAfter;
            
            countAfterStream >> countAfter;
            countAfterStream << afterElementInStrings[1];
            countAfterStream >> userAfter;

            char tmpSymbol = ' ';
            _afterElemenet = new Element(&tmpSymbol, &countAfter, &userAfter);
        } else if (a == '3') {
            std::vector <std::string> afterElementInStrings = parseString(parsedString[2], '|');
            std::stringstream countAfterStream(afterElementInStrings[0]); 
            size_t countAfter;
            size_t userAfter;
            
            countAfterStream >> countAfter;
            countAfterStream << afterElementInStrings[1];
            countAfterStream >> userAfter;

            char tmpSymbol = ' ';
            _afterElemenet = new Element(&tmpSymbol, &countAfter, &userAfter);

            // before element
            std::vector <std::string> beforeElementInStrings = parseString(parsedString[3], '|');
            std::stringstream countBeforeStream(beforeElementInStrings[0]); 
            size_t countBefore;
            size_t userBefore;
            
            countBeforeStream >> countBefore;
            countBeforeStream << beforeElementInStrings[1];
            countBeforeStream >> userBefore;

            tmpSymbol = ' ';
            _beforeElement = new Element(&tmpSymbol, &countBefore, &userBefore);
        }

        // insert element
        std::vector<std::string> insertElementStrings = parseString(parsedString[1], '|');

        std::stringstream countInsertStream(insertElementStrings[0]); 
        size_t countInsert;
        size_t userInsert;
        
        countInsertStream >> countInsert;
        countInsertStream << insertElementStrings[1];
        countInsertStream >> userInsert;

        _insertElement = new Element(&insertElementStrings[3][0], &countInsert, &userInsert);
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

