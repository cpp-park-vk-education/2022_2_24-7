#pragma once
#include <string>

#include "element.hpp"

struct AnswerLinePos {
    AnswerLinePos() :line(0), pos(0) {};

    size_t line;
    size_t pos;
};

class IWorkWithText {
    public:
    // for client part
    virtual std::string insertElementInPosition(size_t position, std::string symbol) = 0;
    virtual std::string deleteElementFromPosition(size_t position) = 0;

    // for server side
    virtual std::string insertElementInPosition(std::string command) = 0;
    virtual std::string deleteElementFromPosition(std::string command) = 0;

    virtual size_t getQuantityOfLines() = 0;
    virtual Element* getStartOfLine(size_t lineNumber) = 0;
    // virtual size_t getSizeOfLine(size_t lineNumber) = 0;

    // virtual AnswerLinePos getLinePosFromPos(size_t pos) = 0;
};
