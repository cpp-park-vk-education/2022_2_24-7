#pragma once
#include <vector>
#include <algorithm>
#include <sstream>

#include "ITextEditor.hpp"
#include "Command.hpp"
// #include "SearcherForPlace.hpp"

struct AnswerForInsertAction {
    AnswerForInsertAction() : quantOfElementsBefore(0) , quantOfLine(0), elementBeforeInsert(nullptr), isEnterBefore(false) {};

    size_t quantOfElementsBefore;
    size_t quantOfLine;
    
    Element* elementBeforeInsert;
    
    bool isEnterBefore;
};


struct StartOfLine {
    StartOfLine(Element* element = nullptr, const size_t sizeOfLine = 0) {
        _elementStart = element;
        _sizeOfLine = sizeOfLine;
        next = nullptr;

        if (!element) {
            size_t a = 0;
            char sym = 'x';
            _elementStart = new Element(&sym, &a, &a);
        }
    };
    
    Element* _elementStart;
    size_t _sizeOfLine;
    
    StartOfLine* next;
};

// struct AnswerLinePos {
//     AnswerLinePos() :line(0), pos(0) {};

//     size_t line;
//     size_t pos;
// };

class Answer;
void searchForElement(Answer& answerWhereElementBefore, Command& com, StartOfLine** line, Element** begginng);

class WorkWithLines : public IWorkWithText {
    public:
    WorkWithLines(size_t UserId = 0, size_t counter = 0);

    // for client part
    std::string insertElementInPosition(size_t position, std::string symbol) override;
    std::string deleteElementFromPosition(size_t position) override;

    // for server side
    std::string insertElementInPosition(std::string command) override;
    std::string deleteElementFromPosition(std::string command) override;

    size_t getQuantityOfLines() override;
    Element* getStartOfLine(size_t lineNumber) override;

    size_t getSizeOfLine(size_t lineNumber) override;
    AnswerLinePos getLinePosFromPos(size_t pos) override;
    
    ~WorkWithLines();

    private:
    AnswerForInsertAction insertElement(Element* insertElement, Element* afterElement = nullptr, Element* beforeElement = nullptr);
    void insertInPositionInLine(size_t positionToInsert, size_t lineWhereInsert, Element* insertElement, Element* beforeInsert);

    void insertEnter(AnswerForInsertAction& receivedAnswer, Element* insertElement);
    AnswerForInsertAction whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line);


    AnswerForInsertAction deleteElement(Element* elementToDelete);
    AnswerForInsertAction whatPositionDelete(Element* elementToDelete);

    void deleteEnter(AnswerForInsertAction answer, StartOfLine* line);
    
    AnswerForInsertAction deleteElementFromLineAndPos(size_t lineWhereToDelete, size_t positionInLine);
    
    AnswerForInsertAction insertElement(Element* insertElement, size_t lineWhereInsert, size_t positionWhereInsert);
    
    
    AnswerLinePos getPosition(size_t position);
    std::string createCommand(bool isDelete, Element* elementOperation, Element* beforeElement  = nullptr, Element* afterElement = nullptr);

    StartOfLine* lines;

    // point to beggining of lines
    Element* beggining;

    size_t lineCount;

    // ISearchForPlace* searcher;
    
    // unique for user
    size_t _counter;
    size_t _UserId;
};