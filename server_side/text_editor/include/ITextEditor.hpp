#pragma once
#include <string>

#include "element.hpp"

class IWorkWithText {
    public:
    // for client part
    virtual std::string insertElementInPosition(size_t lineWhereToPlace, size_t positionInLine, std::string symbol) = 0;
    virtual std::string deleteElementFromPosition(size_t lineWhereToDelete, size_t positionInLine) = 0;

    // for server side
    virtual std::string insertElementInPosition(std::string command) = 0;
    virtual std::string deleteElementFromPosition(std::string command) = 0;

    virtual size_t getQuantityOfLines() = 0;
    virtual Element* getStartOfLine(size_t lineNumber) = 0;
    virtual size_t getSizeOfLine(size_t lineNumber) = 0;
};
