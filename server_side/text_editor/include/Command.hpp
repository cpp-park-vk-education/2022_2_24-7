#pragma once
#include <vector>
#include <sstream>
#include <string>

#include "element.hpp"

struct Command {
    Command(std::string str) {
        _insertElement = nullptr;
        _afterElemenet = nullptr;
        _beforeElement = nullptr;

        std::vector<std::string> parsedString = parseString(str, ':');

        switch (parsedString[parsedString.size()][0])
        {
        case '0':
            // first input
            break;
        case '1':
            // has before element
            
            std::vector <std::string> beforeElementInStrings = parseString(parsedString[2], '|');
            std::stringstream countBeforeStream(beforeElementInStrings[0]); 
            size_t countBefore;
            size_t userBefore;
            
            countBeforeStream >> countBefore;
            countBeforeStream << beforeElementInStrings[1];
            countBeforeStream >> userBefore;

            char tmpSymbol = ' ';
            _beforeElement = new Element(&tmpSymbol, &countBefore, &userBefore);
            break;
        case '2':
            // has element after
            
            std::vector <std::string> afterElementInStrings = parseString(parsedString[2], '|');
            std::stringstream countAfterStream(afterElementInStrings[0]); 
            size_t countAfter;
            size_t userAfter;
            
            countAfterStream >> countAfter;
            countAfterStream << afterElementInStrings[1];
            countAfterStream >> userAfter;

            char tmpSymbol = ' ';
            _afterElemenet = new Element(&tmpSymbol, &countBefore, &userBefore);
            
            break;
        case '3':
            // has after and before
            
            // after element
            std::vector <std::string> afterElementInStrings = parseString(parsedString[2], '|');
            std::stringstream countAfterStream(afterElementInStrings[0]); 
            size_t countAfter;
            size_t userAfter;
            
            countAfterStream >> countAfter;
            countAfterStream << afterElementInStrings[1];
            countAfterStream >> userAfter;

            char tmpSymbol = ' ';
            _afterElemenet = new Element(&tmpSymbol, &countBefore, &userBefore);

            // before element
            std::vector <std::string> beforeElementInStrings = parseString(parsedString[3], '|');
            std::stringstream countBeforeStream(beforeElementInStrings[0]); 
            size_t countBefore;
            size_t userBefore;
            
            countBeforeStream >> countBefore;
            countBeforeStream << beforeElementInStrings[1];
            countBeforeStream >> userBefore;

            char tmpSymbol = ' ';
            _beforeElement = new Element(&tmpSymbol, &countBefore, &userBefore);

            break;
        
        default:
            break;
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

std::vector<std::string> parseString(std::string str, char separator) {
        std::vector <std::string> parseString;
        
        std::stringstream stream(str);
        std::string segmentOfStream;

        while (std::getline(stream,segmentOfStream, separator)) {
            parseString.push_back(segmentOfStream);
        }

        return parseString;
};