// #include "TextEditor.hpp"
#include "../include/TextEditor.hpp"


bool checkForAfterElement(Element* afterElement, Element* checkElement) {
    if (!afterElement) {
        return 1;
    }
    return checkElement->count == afterElement->count && checkElement->UserId == afterElement->UserId;
};

bool checkForBeforeLess(Element* elementBefore, Element* elementAfter) {
    return elementBefore->UserId < elementAfter->UserId;
};


AnswerForInsertAction WorkWithLines::whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line) {
    AnswerForInsertAction answer;
    StartOfLine* tmpLine = line;
    
    if (!beforeInsert->next) {
        if (checkForBeforeLess(beforeInsert, insertElement)) {
            // less than insert
            answer.quantOfElementsBefore = 1;
            answer.elementBeforeInsert = beforeInsert;
        }
        return answer;
    }

    if (checkForBeforeLess(insertElement, beforeInsert->next) || checkForAfterElement(afterElement, beforeInsert->next)) {
        answer.quantOfElementsBefore = 1;
    }


    while (beforeInsert->next && checkForBeforeLess(beforeInsert->next, insertElement) && !checkForAfterElement(afterElement, beforeInsert->next)) {
        if (beforeInsert->isVisible) {
            answer.quantOfElementsBefore++;

            if (beforeInsert->_value == '\n') {
                answer.isEnterBefore = true;
                answer.quantOfElementsBefore = 0;
            }
        }
        
        if (tmpLine && checkForAfterElement(tmpLine->_elementStart, beforeInsert)) {
            answer.quantOfLine++;
            answer.isEnterBefore = false;
            answer.quantOfElementsBefore = 1;
            
            tmpLine = tmpLine->next;
        }
        
        beforeInsert = beforeInsert->next;
        answer.elementBeforeInsert = beforeInsert;
    }

    return answer;
};

void WorkWithLines::insertInPositionInLine(size_t positionToInsert, size_t lineWhereInsert, Element* insertElement, Element* beforeInsert) {
    if (lineWhereInsert == 0) {
        // input in first line
        
        if (lines) {
            // first line exist

            if (positionToInsert == 0) {
                if (lines->_sizeOfLine == 0) {
                    delete lines->_elementStart;
                }

                insertElement->next = beggining;
                beggining = insertElement;
                
                lines->_elementStart = beggining;
                lines->_sizeOfLine++;
                return;
            }

            Element* tmpElement = lines->_elementStart;

            size_t elementPosition = 1;
            while (elementPosition < positionToInsert) {
                tmpElement = tmpElement->next;

                if (tmpElement->isVisible) {
                    elementPosition++;
                }
            }

            insertElement->next = tmpElement->next;
            tmpElement->next = insertElement;
            
            lines->_sizeOfLine++;
        } else {
            // first line doesnt exist
            lines = new StartOfLine(insertElement, 1);
            lineCount++;
        }
    } else {
        // not first line

        StartOfLine* insertLine = lines;
        size_t linePos = lineWhereInsert;

        if (positionToInsert == 0) {
            lineWhereInsert--;
        }

        for (size_t i = 0; i < lineWhereInsert; i++) {
            insertLine = insertLine->next;
        }
        
        Element* before = insertLine->_elementStart;
        
        if (positionToInsert == 0) {
            while (before->next != insertLine->next->_elementStart) {
                before = before->next;
            }

            if (insertLine->_sizeOfLine == 0) {
                delete insertLine->_elementStart;                
            }

            insertElement->next = before->next;
            before->next = insertElement;

            insertLine->next->_sizeOfLine++;
            insertLine->next->_elementStart = insertElement;

        } else {
            size_t positionNow = 1;

            while (positionNow < positionToInsert) {
                before = before->next;

                if (before->isVisible) {
                    positionNow++;
                }
            }

            insertElement->next = before->next;
            before->next = insertElement;

            insertLine->_sizeOfLine++;
        }
        
    }
};

AnswerForInsertAction WorkWithLines::insertElement(Element* insertElement, Element* afterElement, Element* beforeElement) {
    // первый блок, вставляется элемент
    AnswerForInsertAction answer;

    Element* tmpBefore = nullptr;
    Element* tmpAfter = nullptr;
    
    StartOfLine* tmpLine = lines;

    if (beforeElement) {
        // element before exist
        tmpBefore = beggining;
        while (tmpBefore && !checkForAfterElement(beforeElement, tmpBefore)) {
            tmpBefore = tmpBefore->next;
        }

    } else {
        if (beggining) {
            // elements exist
            tmpBefore = beggining;
        } else {
            // elements doesnt exist
            // what position
            beggining = insertElement;
            lines = new StartOfLine(insertElement, 1);
            return answer;
        }

    }

    // search for start position
    answer = whatPosition(tmpBefore, insertElement, afterElement, tmpLine);

    insertInPositionInLine(answer.quantOfElementsBefore, answer.quantOfLine, insertElement, answer.elementBeforeInsert);

    insertEnter(answer, insertElement);
};

void WorkWithLines::insertEnter(AnswerForInsertAction& receivedAnswer, Element* insertElement) {
    if (insertElement->_value != '\n') {
        return;
    }
    // insert after \n

    StartOfLine* tmpLine = lines;

    for (size_t i = 0; i < receivedAnswer.quantOfLine; ++i) {
        tmpLine = tmpLine->next;
    }

    Element* startOfLine = insertElement->next;
    bool isNewLine = false;

    while (startOfLine && !startOfLine->isVisible) {
        startOfLine = startOfLine->next;
        
        if (tmpLine->next && startOfLine == tmpLine->next->_elementStart) {
            isNewLine = true;
            break;
        }
    }
    
    StartOfLine* newLine;
    if (isNewLine) {
        newLine = new StartOfLine();
    } else {
        newLine = new StartOfLine(startOfLine, 1);
    }
    
    newLine->_sizeOfLine += tmpLine->_sizeOfLine - receivedAnswer.quantOfElementsBefore - 2;
    tmpLine->_sizeOfLine -= newLine->_sizeOfLine;

    newLine->next = tmpLine->next;
    tmpLine->next = newLine;
    
    lineCount++;
};


AnswerForInsertAction WorkWithLines::whatPositionDelete(Element* elementToDelete) {
    AnswerForInsertAction answer;

    if (checkForAfterElement(beggining, elementToDelete)) {
        return answer;
    }

    answer.elementBeforeInsert = lines->_elementStart;

    StartOfLine* tmpLine = lines;
    Element* tmpElement = beggining;

    while (!checkForAfterElement(tmpElement, elementToDelete)) {
        
        if (tmpLine->_elementStart == tmpElement) {
            answer.quantOfLine++;
            answer.isEnterBefore = false;
            
            tmpLine = tmpLine->next;
        }
        
        if (tmpElement->isVisible && tmpElement->_value == '\n') {
            answer.isEnterBefore = true;
        }

        answer.elementBeforeInsert = tmpElement;
        tmpElement = tmpElement->next;
    }

    return answer;
};

AnswerForInsertAction WorkWithLines::deleteElement(Element* elementToDelete) {
    AnswerForInsertAction answer;
    bool firstPos = false;
    
    AnswerForInsertAction positions = whatPositionDelete(elementToDelete);

    if (positions.quantOfLine == 0 && positions.quantOfElementsBefore == 0) {
        firstPos = true;
    }
    
    StartOfLine* tmpLine = lines;
    StartOfLine* lineBefore = nullptr;
    
    if (positions.quantOfLine != 0) {
        for (size_t i = 1; i < positions.quantOfLine - 1; ++i) {
            tmpLine = tmpLine->next;
        }
        lineBefore = tmpLine;
        tmpLine = tmpLine->next;
    }

    if (positions.isEnterBefore || firstPos) {
        // first element

        if (tmpLine->_sizeOfLine == 1) {
            // last sumbol
            answer.isEnterBefore = true;
            tmpLine->_elementStart->isVisible = false;

            if (lineBefore) {
                if (tmpLine->next) {
                    // not last line
                    lineBefore->next = tmpLine->next;
                    
                    delete tmpLine;
                } else {
                    // last line
                    tmpLine->_sizeOfLine = 0;
                }
            } else {
                // first line
                if (!tmpLine->next) {
                    lineCount--;
                    
                    delete lines;
                } else {
                    lines = lines->next;
                    lineCount--;
                    
                    delete tmpLine;
                }
            }

        } else {
            // not last symbol
            Element* firstVisible = tmpLine->_elementStart->next;
            
            while (!firstVisible->isVisible) {
                firstVisible = firstVisible->next;
            }

            tmpLine->_sizeOfLine--;
            tmpLine->_elementStart->isVisible = false;
            tmpLine->_elementStart = firstVisible;
        }

    } else {
        // not first element
        
        tmpLine->_sizeOfLine--;
        positions.elementBeforeInsert->next->isVisible = false;
    }

    if (!answer.isEnterBefore) {
        deleteEnter(answer, tmpLine);
    }
};

void WorkWithLines::deleteEnter(AnswerForInsertAction answer, StartOfLine* line) {
    Element* tmpElement;
    if (!answer.elementBeforeInsert) {
        tmpElement = beggining;
    } else {
        tmpElement = answer.elementBeforeInsert->next;
    }
    
    if (tmpElement->_value != '\n') {
        return;
    }

    StartOfLine* tmpDelete = line->next;
    line->_sizeOfLine += line->next->_sizeOfLine;
    line->next = line->next->next;

    if (tmpDelete->_sizeOfLine == 0) {
        delete tmpDelete->_elementStart;
    }

    delete tmpDelete;
};



bool funcWithBefore(Element* el, Element* beforeElement) {
    if (beforeElement)  {
        return el->count == beforeElement->count && beforeElement->UserId == el->UserId;
    } else {
        return true;
    }
};

void insertBeforeFirstElement(Element* insertElement, Element** beggining, StartOfLine** lines) {
    insertElement->next = (*beggining);
    if ((*lines)) {
        (*lines)->_elementStart = insertElement;
        (*lines)->_sizeOfLine++;
    } else {
        (*lines) = new StartOfLine(insertElement, 1);
    }
    (*beggining) = insertElement;
};


struct Answer {
    Answer() : answerElement(nullptr), answerLine(nullptr), linePos(0), afterEnter(false) {};

    Element * answerElement;
    StartOfLine* answerLine;
    size_t linePos;


    bool afterEnter;
};

struct AnswerDelete {
    AnswerDelete() : answerElement(nullptr), answerLine(nullptr), isDeleteBeggining(false), isNext(false) {};

    Element * answerElement;
    StartOfLine* answerLine;
    
    bool isNext;
    bool isDeleteBeggining;
};

AnswerDelete searchForBeforeDeleteElement(Element* beggining, Element* deleteElement, StartOfLine **lines) {
    AnswerDelete answer;

    Element* tmp = beggining;
    
    StartOfLine* tmpLine = (*lines);
    StartOfLine* tmpLineBefore = nullptr;

    bool isEnter = false;
    bool isLineStart = false;

    if (beggining->count == deleteElement->count && beggining->UserId == deleteElement->UserId) {
        answer.answerElement = beggining;
        answer.isDeleteBeggining = true;
        return answer;
    }

    if (tmp->next) {
        // elements after beggining

        while (tmp->next && !(tmp->next->count == deleteElement->count && tmp->next->UserId == deleteElement->UserId)) {
            isLineStart = false;

            if (tmpLine && tmpLine->_elementStart == tmp) {
                tmpLineBefore = tmpLine;
                tmpLine = tmpLine->next;

                isLineStart = true;
                isEnter = false;
                answer.isNext = true;
            }

            tmp = tmp->next;
        }
        answer.answerElement = tmp;
        if (!tmpLineBefore) {
            answer.isNext = false;
            tmpLineBefore = (*lines);
        }

        answer.answerLine = tmpLineBefore;
        answer.isDeleteBeggining = false;
        answer.isNext = false;

    } else {
        // next element doesn't exist
        answer.answerElement = tmp;
        answer.isDeleteBeggining = true;
        answer.isNext = false;
    }

    return answer;

}

Answer searchForElement(Element* fromWhere, Element* whatSearch, StartOfLine* firstLine) {
    Answer answer;
    
    if (fromWhere && whatSearch) {
        Element* tmp = fromWhere;
        StartOfLine* line = firstLine;
        StartOfLine* beforeLine = nullptr;
        size_t lineCount = 0;
        bool enter = false;

        while (tmp) {
            if (tmp->_value == '\n' && tmp->isVisible) {
                enter = true;
            }

            if (line && line->_elementStart == tmp) {
                beforeLine = line;
                line = line->next;
                lineCount++;
                enter = false;
            }
            
            if (tmp->count == whatSearch->count && tmp->UserId == whatSearch->UserId) {
                break;
            }

            tmp = tmp->next;
        }

        answer.answerElement = tmp;
        answer.answerLine = beforeLine;
        answer.linePos = lineCount;
        answer.afterEnter = enter;

        return answer;
    }
    
    return answer;
};

WorkWithLines::WorkWithLines(size_t UserId, size_t counter) :  lineCount(0), _counter(counter), _UserId(UserId) {
    // searcher = new Searcher(this);
    lines = nullptr;
    beggining = nullptr;
};

void insertElement(Element* startOfLine, Element* whatInsert, Element* afterWhatInsert, Element* beforeWhatInsert, StartOfLine** lines) {
    // сделать проверку про 
    // TODO проверить на before element, чтобы можно вставить перед элементами других людей
    if (afterWhatInsert) {
        // after insert
        if (beforeWhatInsert) {
            // after and before insert
            Element* tmp = afterWhatInsert;
            // beggining exist
            while (tmp->UserId < whatInsert->UserId) {
                // skip another elements with less userid
                tmp = tmp->next;
            }
            whatInsert->next = tmp->next;
            tmp->next = whatInsert;
        } else {
            // only after insert
            Element* tmp = afterWhatInsert;
            // beggining exist
            while (tmp->UserId < whatInsert->UserId) {
                // skip another elements with less userid
                tmp = tmp->next;
            }
            whatInsert->next = tmp->next;
            tmp->next = whatInsert;
        }
    } else {
        if (beforeWhatInsert) {
            // before insert
            Element* tmp = startOfLine;
            // beggining exist
            while (tmp->UserId < whatInsert->UserId) {
                // skip another elements with less userid
                tmp = tmp->next;
            }
            whatInsert->next = tmp->next;
            tmp->next = whatInsert;
        } else {
            // insert into beggining
            if (startOfLine) {
                Element* tmp = startOfLine;
                // beggining exist
                while (tmp->UserId < whatInsert->UserId) {
                    // skip another elements with less userid
                    tmp = tmp->next;
                }
                whatInsert->next = tmp->next;
                tmp->next = whatInsert;

            } else {
                // beggining doesnt exist
                startOfLine = whatInsert;
            }
        }
    }
}


std::string WorkWithLines::insertElementInPosition(size_t lineWhereToPlace, size_t positionInLine, std::string symbol) {
    Element* afterThis = nullptr;
    // TODO убрать всё в Searcher

    if (positionInLine == 0) {
        if (lineWhereToPlace == 0) {
            // first line first position
            if (!beggining) {
                // first input
                beggining = new Element(&symbol[0], &(++_counter), &_UserId);
                lines = new StartOfLine(beggining, 1);
                lineCount++;
            } else {
                // not first input
                if (lines) {
                    // lines exist
                    Element* searchElement = beggining;
                
                    for (size_t i = 0; i < 1; ) {
                        if (searchElement->next && searchElement->next->isVisible) {
                            ++i;
                        } else if (searchElement->isVisible) {
                            ++i;
                        } else {
                            searchElement = searchElement->next;
                        }
                    }
                    if (searchElement->isVisible) {
                        // beeggining
                        Element* tmp = beggining;
                        beggining = new Element(&symbol[0], &(++_counter), &_UserId);
                        beggining->next = tmp;

                        lines->_elementStart = beggining;
                        lines->_sizeOfLine++;
                    } else {
                        Element* tmp = new Element(&symbol[0], &(++_counter), &_UserId);
                        tmp->next = searchElement->next;
                        searchElement->next = tmp;
                        lines->_sizeOfLine++;
                        
                        afterThis = searchElement;
                    }

                } else {
                    // lines doesnt exist
                    Element* tmp = new Element(&symbol[0], &(++_counter), &_UserId);
                    lines = new StartOfLine(tmp, 1);
                    tmp->next = beggining->next;
                    beggining->next = tmp;
                    lineCount++;

                    afterThis = beggining;
                }
                
                
            }
        } else {
            // first position
            StartOfLine *searchLineBefore = lines;
            for (size_t i = 0; i < lineWhereToPlace - 1; ++i) {
                searchLineBefore = searchLineBefore->next;
            }

            Element* searchElementBefore = searchLineBefore->_elementStart;
            while (!(searchElementBefore->_value == '\n' && searchElementBefore->isVisible)) {
                searchElementBefore = searchElementBefore->next;
            }
            
            Element* tmp = new Element(&symbol[0], &(++_counter), &_UserId);
            
            tmp->next = searchElementBefore->next;
            searchElementBefore->next = tmp;
            
            if (searchLineBefore->next->_sizeOfLine == 0) {
                tmp->next = searchLineBefore->next->_elementStart->next;
                delete searchLineBefore->next->_elementStart;
            }

            searchLineBefore->next->_elementStart = tmp;
            searchLineBefore->next->_sizeOfLine++;
            

            afterThis = searchElementBefore;
        }
    } else {
        // not first position
        StartOfLine *searchLine = lines;
        if (lineWhereToPlace != 0) {
            for (size_t i = 0; i < lineWhereToPlace; ++i) {
                searchLine = searchLine->next;
            }
        }

        Element* searchElementBefore = searchLine->_elementStart;
        for (size_t i = 0; i < positionInLine - 1; ) {
            if (searchElementBefore->isVisible) {
                ++i;
            }
            searchElementBefore = searchElementBefore->next;
        }

        // if (positionInLine == 1) {
        //     searchElementBefore = searchElementBefore->next;
        // }

        Element* tmp = new Element(&symbol[0], &(++_counter), &_UserId);
        
        tmp->next = searchElementBefore->next;
        searchElementBefore->next = tmp;

        searchLine->_sizeOfLine++;

        afterThis = searchElementBefore;
    }

    if (symbol[0] == '\n') {
        StartOfLine* newLine = new StartOfLine();
        lineCount++;
        if (!afterThis) {
            // beggining
            beggining->next = newLine->_elementStart;
            newLine = lines->next;
            lines->next = newLine;
        } else {
            // not beggining
            if (lineWhereToPlace == 0) {
                // first line
                Element* tmp = afterThis;
                
                while (tmp->next && !tmp->next->isVisible) {
                    tmp = tmp->next;
                }

                if (!lines->next) {
                    afterThis->next->next = newLine->_elementStart;
                    newLine->next = lines->next;
                    lines->next = newLine;
                }
                else if (lines->next->_elementStart == tmp) {
                    // not elements
                    newLine->next = lines->next;
                    lines->next = newLine;
                } else {
                    if (tmp->next) {
                        // elements exist
                        newLine->_elementStart = tmp->next;
                        newLine->next = lines->next;
                        lines->next = newLine;
                    } else {
                        // doesnt exist
                        newLine->next = lines->next;
                        lines->next = newLine;
                    }
                }

            } else {
                // not first line TOOD check
                StartOfLine* lineSearchBefore = lines;
                for (size_t i = 0; i < lineWhereToPlace; ++i) {
                    lineSearchBefore = lineSearchBefore->next;
                }

                newLine->next = lineSearchBefore->next;
                lineSearchBefore->next = newLine;
            }
        }
    }

    // first part of command
    std::string firstPartOfCommand = std::to_string(_counter) + '|' + std::to_string(_UserId) + '|' + symbol[0];
    std::string secondPartOfCommand = "";
    std::string thirdPartOfCommand = "";
    size_t partsCount = 0;

    std::string commandToReturn = "i:" + firstPartOfCommand;
    if (afterThis) {
        //before element exist
        secondPartOfCommand = std::to_string(afterThis->count) + '|' + std::to_string(afterThis->UserId);
        commandToReturn += ':' + secondPartOfCommand;
        partsCount += 1;

        if (afterThis->next->next && afterThis->next->next->count != 0) {
            // after element exist
            thirdPartOfCommand = std::to_string(afterThis->next->next->count) + '|' + std::to_string(afterThis->next->next->UserId);
            commandToReturn += ':' + thirdPartOfCommand;
            
            partsCount += 2;
        }
    } else {
        if (beggining->next) {
            // after element exist
            thirdPartOfCommand = std::to_string(beggining->next->count) + '|' + std::to_string(beggining->next->UserId);
            commandToReturn += ':' + thirdPartOfCommand;

            partsCount += 2;
        }
    }
    commandToReturn += ':' + std::to_string(partsCount);

    // TODO подставить сразу без переменной
    return commandToReturn;
};

std::string WorkWithLines::deleteElementFromPosition(size_t lineWhereToDelete, size_t positionInLine) {
    Element* afterWhatElement = nullptr;
    Element* deletionElement = nullptr;
    
    StartOfLine* beforeDeletionLine = nullptr;
    StartOfLine* deletionLine = nullptr;
    bool isDeleteLine = false;

    if (lineWhereToDelete != 0) {
        beforeDeletionLine = lines;
        for (size_t i = 0; i < lineWhereToDelete - 1; ++i) {
            beforeDeletionLine = beforeDeletionLine->next;
        }
        deletionLine = beforeDeletionLine->next;
    } else {
        deletionLine = lines;
    }
    
    if (positionInLine == 0) {
        // first element delete 
        if (deletionLine->_sizeOfLine == 1) {
            // last symbol delete
            
            isDeleteLine = true;
            lineCount--;
            
            if (lineWhereToDelete == 0) {
                // delete from first line
                lines = lines->next;

                deletionLine->_elementStart->isVisible = false;
                deletionElement = deletionLine->_elementStart;

            
                delete deletionLine;
            } else {
                // delete not from first line

                beforeDeletionLine->next = deletionLine->next;

                deletionLine->_elementStart->isVisible = false;
                deletionElement = deletionLine->_elementStart;

                if (lineWhereToDelete == lineCount - 1) {
                    // last line
                    beforeDeletionLine->next = new StartOfLine();
                    deletionElement->next = beforeDeletionLine->next->_elementStart;
                    lineCount++;
                }

                delete deletionLine;
            }
        } else {
            // not last symbol delete
        
            Element* nextVisible = deletionLine->_elementStart->next;
            while (!nextVisible->isVisible) {
                nextVisible = nextVisible->next;
            }

            deletionElement = deletionLine->_elementStart;
            
            deletionLine->_elementStart->isVisible = false;
            deletionLine->_elementStart = nextVisible;
        }
    } else {
        // not first element delete
        
        Element* tmp = deletionLine->_elementStart;
        for (size_t i = 0; i < positionInLine; ) {
            if (tmp->isVisible) {
                ++i;
            }
            tmp = tmp->next;
        }
        while (!tmp->isVisible) {
            tmp = tmp->next;
        }
        deletionElement = tmp;

        tmp->isVisible = false;
    }

    if (deletionElement->_value == '\n' && !isDeleteLine) {
        // ERROR can be error
        
        StartOfLine* tmp = deletionLine->next;
        deletionLine->next = deletionLine->next->next;
        
        lineCount--;
        delete tmp;
    }
    
    // output command
    // first part of command
    _counter++;

    std::string firstPartOfCommand = std::to_string(deletionElement->count) + '|' + std::to_string(deletionElement->UserId) + '|' ;

    std::string commandToReturn = "d:" + firstPartOfCommand;

    return commandToReturn;
};

std::string WorkWithLines::insertElementInPosition(std::string command) {
    Command com(command);
    // Answer answerWhereElementBefore = searchForElement(beggining, com._afterElemenet,lines);

    insertElement(com._insertElement, com._afterElemenet, com._beforeElement);

    return command;
};

std::string WorkWithLines::deleteElementFromPosition(std::string command) {
    Command com(command);
    
    deleteElement(com._insertElement);

    return command;
};

size_t WorkWithLines::getQuantityOfLines() {
    return lineCount;
};

Element* WorkWithLines::getStartOfLine(size_t lineNumber) {
    if (!lines) {
        return nullptr;
    }

    if (lineNumber <= lineCount) {
        StartOfLine* searchForStart = lines;   
        for(size_t i = 0; i < lineNumber; ++i) {
            searchForStart = searchForStart->next;
        }
        
        return searchForStart->_elementStart;
    }
    return nullptr;
};

size_t WorkWithLines::getSizeOfLine(size_t lineNumber) {
    if (lineNumber <= lineCount) {
        StartOfLine* searchForStart;   
        for(size_t i = 0; i < lineNumber; ++i) {
            searchForStart = searchForStart->next;
        }
        
        return searchForStart->_sizeOfLine;
    }
    return 0;
};

WorkWithLines::~WorkWithLines() {
    Element* tmp = beggining;

    while(tmp) {
        Element* deleteElement = tmp;
        tmp = tmp->next;
        delete deleteElement;
    }

    StartOfLine* tmpLine = lines;
    while(tmpLine) {
        StartOfLine* tmp = tmpLine;
        tmpLine = tmpLine->next;
        
        delete tmp;
    }
};


// void searchWithoutLines(Answer* answer, Command& command, StartOfLine** line, Element* beggining) {

// }



void searchForElement(Answer& answerWhereElementBefore, Command& com, StartOfLine** line, Element** begginng) {
    Element* tmp = (*begginng);
    StartOfLine* tmpLine = (*line);

    if (answerWhereElementBefore.answerElement) {
        tmp = answerWhereElementBefore.answerElement;
    }

    if (answerWhereElementBefore.answerLine) {
        tmpLine = answerWhereElementBefore.answerLine;
    }

    StartOfLine* beforeLine = nullptr;
    bool isSearchWas = false;

    if (tmp->next && answerWhereElementBefore.answerElement) {
        while (tmp->next && tmp->next->UserId < com._insertElement->UserId && funcWithBefore(tmp->next, com._beforeElement)) {
            if (tmp->_value == '\n' && tmp->isVisible) {
                answerWhereElementBefore.afterEnter = true;
            }

            if (tmpLine && tmpLine->_elementStart == tmp) {
                beforeLine = tmpLine;
                tmpLine = tmpLine->next;
                
                answerWhereElementBefore.afterEnter = false;
            }

            isSearchWas = true;
            tmp = tmp->next;
        }

        if (!isSearchWas) {
            com._insertElement->next = tmp->next;
            tmp->next = com._insertElement;

            if (answerWhereElementBefore.afterEnter) {
                tmpLine->next->_elementStart = com._insertElement;
                tmpLine->next->_sizeOfLine++;

                answerWhereElementBefore.answerLine = tmpLine->next;
            } else {
                tmpLine->_sizeOfLine++;
                answerWhereElementBefore.answerLine = tmpLine;
            }

        } else {
            if (beforeLine) {
                
                com._insertElement->next = tmp->next;
                tmp->next = com._insertElement;

                answerWhereElementBefore.answerElement = tmp;

                if (answerWhereElementBefore.afterEnter) {
                    if (beforeLine->next->_sizeOfLine == 0) {
                        // существуетп пустой элемент
                        
                        if (com._insertElement->next == beforeLine->next->_elementStart) {
                            com._insertElement->next = nullptr;
                        }
                        
                        delete beforeLine->next->_elementStart;
                    }
                    beforeLine->next->_sizeOfLine++;
                    beforeLine->next->_elementStart = com._insertElement;
                    answerWhereElementBefore.answerLine = beforeLine->next;

                } else {
                    beforeLine->_sizeOfLine++;
                    answerWhereElementBefore.answerLine = beforeLine;
                }
            } else {
                // if (tmp == begginng && answerWhereElementBefore.linePos != 0)
                com._insertElement->next = tmp->next;
                tmp->next = com._insertElement;
                
                if (answerWhereElementBefore.afterEnter) {
                    if (tmpLine->_sizeOfLine == 0) {
                        delete tmpLine->_elementStart;
                    }
                    
                    tmpLine->next->_elementStart = com._insertElement;
                    tmpLine->next->_sizeOfLine++;
                    
                    answerWhereElementBefore.answerLine = tmpLine->next;
                } else {
                    tmpLine++;
                    answerWhereElementBefore.answerLine = tmpLine;
                }
            }
        }
    } else {
        if (tmp == (*begginng)) {
            // start of line
            if (tmp->UserId < com._insertElement->UserId) {
                // beggining userid less then insert
                com._insertElement->next = (*begginng)->next;
                (*begginng)->next = com._insertElement;

                if ((*begginng)->isVisible && (*begginng)->_value == '\n') {
                    (*line)->next->_elementStart = com._insertElement;
                    (*line)->next->_sizeOfLine++;
                    answerWhereElementBefore.answerLine = (*line)->next;
                } else {
                    (*line)->_sizeOfLine++;
                    answerWhereElementBefore.answerLine = (*line);
                }

            } else {
                // beggining userid more or equal then insert
                insertBeforeFirstElement(com._insertElement, begginng, line);
                answerWhereElementBefore.answerLine = (*line);
            }
        } else {
            // end of line
            com._insertElement->next = tmp->next;
            tmp->next = com._insertElement;

            if (answerWhereElementBefore.afterEnter || (tmp->isVisible && tmp->_value == '\n')) {
                if (answerWhereElementBefore.answerLine->next->_sizeOfLine == 0) {
                    delete answerWhereElementBefore.answerLine->next->_elementStart;
                }

                answerWhereElementBefore.answerLine->next->_elementStart = com._insertElement;
                answerWhereElementBefore.answerLine->next->_sizeOfLine++;

                answerWhereElementBefore.answerLine = answerWhereElementBefore.answerLine->next;
            } else {
                answerWhereElementBefore.answerLine->_sizeOfLine++;
                answerWhereElementBefore.answerLine = answerWhereElementBefore.answerLine;
            }

        }
    }
};

AnswerLinePos WorkWithLines::getLinePosFromPos(size_t pos) {
    AnswerLinePos answ;
    StartOfLine* tmp = lines;

    while (tmp) {
        if (pos > tmp->_sizeOfLine) {
            pos -= tmp->_sizeOfLine;
            answ.line++;
        } else {
            break;
        }
        tmp = tmp->next;
    }
        
    answ.pos = pos;
    return answ;
};

