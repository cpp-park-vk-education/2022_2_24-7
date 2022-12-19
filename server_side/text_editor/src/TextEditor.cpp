#include <iostream>

#include "TextEditor.hpp"


AnswerForInsertAction WorkWithLines::whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line) {
   AnswerForInsertAction answer;
   return answer;
};

void WorkWithLines::insertInPositionInLine(size_t positionToInsert, size_t lineWhereInsert, Element* insertElement, Element* beforeInsert) {
};

AnswerForInsertAction WorkWithLines::insertElement(Element* insertElement, Element* afterElement, Element* beforeElement) {
    AnswerForInsertAction answer;
    
    return answer;
};

void WorkWithLines::insertEnter(AnswerForInsertAction& receivedAnswer, Element* insertElement) {
};


AnswerForInsertAction WorkWithLines::whatPositionDelete(Element* elementToDelete) {
   AnswerForInsertAction answer;
   return answer;
};

void WorkWithLines::deleteEnter(AnswerForInsertAction answer, StartOfLine* line) {
};

WorkWithLines::WorkWithLines(size_t UserId, size_t counter) : beggining(nullptr), lines(nullptr), lineCount(0), _counter(counter), _UserId(UserId) {
    lines = nullptr;
    beggining = nullptr;

    searcher = new Searcher;
};

std::string WorkWithLines::insertElementInPosition(size_t position, std::string symbol) {
    std::string command;
    return command;
};

std::string WorkWithLines::deleteElementFromPosition(size_t position) {
    std::string command;
    return command;
};

std::string WorkWithLines::insertElementInPosition(std::string command) {
    std::string command1;
    return command1;
};

std::string WorkWithLines::deleteElementFromPosition(std::string command) {
    std::string returnString;
    return returnString;
};

size_t WorkWithLines::getQuantityOfLines() {
    return lineCount;
};

Element* WorkWithLines::getStartOfLine(size_t lineNumber) {
    return nullptr;
};


std::string WorkWithLines::createCommand(bool isDelete, Element* elementOperation, Element* beforeElement, Element* afterElement) {
    std::string returnCommand;

    return returnCommand;
};

AnswerForInsertAction WorkWithLines::insertElement(Element* insertElement, size_t lineWhereInsert, size_t positionWhereInsert) {
    AnswerForInsertAction answer;

    return answer;
};

AnswerLinePos WorkWithLines::getPosition(size_t position) {
    AnswerLinePos answer;
   
    return answer;
};

AnswerForInsertAction WorkWithLines::deleteElementFromLineAndPos(size_t lineWhereToDelete, size_t positionInLine) {
    AnswerForInsertAction answer;
    return answer;
};


WorkWithLines::~WorkWithLines() {
    delete searcher;
};

