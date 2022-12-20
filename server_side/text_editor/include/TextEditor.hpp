#pragma once
#include <vector>
#include <algorithm>
#include <sstream>

#include "ITextEditor.hpp"
#include "Command.hpp"

#include "StartOfLine.hpp"
#include "Answer.hpp"   

#include "SearcherForPlace.hpp"

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
    
    ~WorkWithLines() override;

    private:
    AnswerLinePos getPosition(size_t position);
    
    AnswerForInsertAction whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line);
    AnswerForInsertAction whatPositionDelete(Element* elementToDelete);
    

    AnswerForInsertAction insertElement(Element* insertElement, Element* afterElement = nullptr, Element* beforeElement = nullptr);
    AnswerForInsertAction insertElement(Element* insertElement, size_t lineWhereInsert, size_t positionWhereInsert);
    
    void insertInPositionInLine(size_t positionToInsert, size_t lineWhereInsert, Element* insertElement, Element* beforeInsert);


    AnswerForInsertAction deleteElementFromLineAndPos(size_t lineWhereToDelete, size_t positionInLine);    


    void insertEnter(AnswerForInsertAction& receivedAnswer, Element* insertElement);
    void deleteEnter(AnswerForInsertAction answer, StartOfLine* line);
    
    
    std::string createCommand(bool isDelete, Element* elementOperation, Element* beforeElement  = nullptr, Element* afterElement = nullptr);

    ISearchForPlace *searcher;

    StartOfLine* lines;
    size_t lineCount;
    
    Element* beggining;
    
    // unique for user
    size_t _counter;
    size_t _UserId;
};
