#pragma once
#include <vector>

#include "ITextEditor.hpp"
// #include "SearcherForPlace.hpp"

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

class WorkWithLines : public IWorkWithText {
    public:
    WorkWithLines(size_t UserId = 0, size_t counter = 0);

    // for client part
    std::string insertElementInPosition(size_t lineWhereToPlace, size_t positionInLine, std::string symbol) override;
    std::string deleteElementFromPosition(size_t lineWhereToDelete, size_t positionInLine) override;

    // for server side
    std::string insertElementInPosition(std::string command) override;
    std::string deleteElementFromPosition(std::string command) override;

    size_t getQuantityOfLines() override;
    Element* getStartOfLine(size_t lineNumber) override;

    size_t getSizeOfLine(size_t lineNumber) override;
    ~WorkWithLines();

    private:
    StartOfLine* lines;

    // point to beggining of lines
    Element* beggining;

    size_t lineCount;

    // ISearchForPlace* searcher;
    
    // unique for user
    size_t _counter;
    size_t _UserId;
};