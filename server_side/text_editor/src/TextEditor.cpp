#include "TextEditor.hpp"
// #include "../include/TextEditor.hpp"
#include <iostream>



AnswerForInsertAction WorkWithLines::whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line) {
   return searcher->whatPosition(beforeInsert, insertElement, afterElement, line);
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

            Element* tmpElement = searcher->getToPosition(lines->_elementStart, positionToInsert);

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

        insertLine = searcher->getToLine(insertLine, lineWhereInsert);
        
        Element* before = insertLine->_elementStart;
        
        if (positionToInsert == 0) {
            before = searcher->getToEndOfLine(before);
            before = searcher->skipInvisibleElements(before);

            if (insertLine->next->_sizeOfLine == 0) {
                delete insertLine->next->_elementStart;                
            }

            insertElement->next = before->next;
            before->next = insertElement;

            insertLine->next->_sizeOfLine++;
            insertLine->next->_elementStart = insertElement;
        } else {
            before = searcher->getToPosition(before, positionToInsert);

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

    size_t countVisibleBefore = 0;
    size_t lineCountBefore = 0;

    if (beforeElement) {
        // element before exist
        tmpBefore = beggining;
        StartOfLine* tmpLine = lines;

        checkForNotEqual notEq;

        AnswerForLineAndElementVisible answer = searcher->searchForLineAndPos(tmpBefore, beforeElement, tmpLine, &notEq);
            
        tmpBefore = answer.element;
        tmpLine = answer.line;

        countVisibleBefore = answer.visibleCount;
        lineCountBefore = answer.lineCount;

    } else {

        if (beggining) {
            // elements exist
            tmpBefore = beggining;

            checkForLess less;

            AnswerForLineAndElementVisible answer = searcher->searchForLineAndPos(tmpBefore, insertElement, tmpLine, &less);
            
            tmpBefore = answer.element;
            tmpLine = answer.line;

            countVisibleBefore = answer.visibleCount;
            lineCountBefore = answer.lineCount;
        } else {
            // elements doesnt exist
            // what position
            beggining = insertElement;
            lines = new StartOfLine(insertElement, 1);
            return answer;
        }

    }

    // search for start position
    if (beforeElement) {
        // answer = whatPosition(tmpBefore, insertElement, afterElement, tmpLine);
        answer = whatPosition(tmpBefore, insertElement, afterElement, tmpLine);
    }

    answer.quantOfElementsBefore += countVisibleBefore;
    answer.quantOfLine += lineCountBefore;

    insertInPositionInLine(answer.quantOfElementsBefore, answer.quantOfLine, insertElement, answer.elementBeforeInsert);

    insertEnter(answer, insertElement);
    
    return answer;
};

void WorkWithLines::insertEnter(AnswerForInsertAction& receivedAnswer, Element* insertElement) {

    if (insertElement && insertElement->_value != '\n') {
        return;
    }
    // insert after \n

    // StartOfLine* tmpLine = lines;
    StartOfLine* tmpLine = searcher->getToLine(lines, receivedAnswer.quantOfLine);

    // for (size_t i = 0; i < receivedAnswer.quantOfLine; ++i) {
    //     tmpLine = tmpLine->next;
    // }

    Element* startOfLine = insertElement->next;
    bool isNewLine = false;

    if (!startOfLine) {
        isNewLine = true;
    }


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
    
    newLine->_sizeOfLine = tmpLine->_sizeOfLine - receivedAnswer.quantOfElementsBefore - 1;
    tmpLine->_sizeOfLine -= newLine->_sizeOfLine;

    newLine->next = tmpLine->next;
    tmpLine->next = newLine;
    
    lineCount++;
};


AnswerForInsertAction WorkWithLines::whatPositionDelete(Element* elementToDelete) {
   return searcher->whatPositionDelete(elementToDelete, beggining, lines);
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

WorkWithLines::WorkWithLines(size_t UserId, size_t counter) : beggining(nullptr), lines(nullptr), lineCount(0), _counter(counter), _UserId(UserId) {
    // searcher = new Searcher(this);
    lines = nullptr;
    beggining = nullptr;

    searcher = new Searcher;
};

std::string WorkWithLines::insertElementInPosition(size_t position, std::string symbol) {
    Element* _insertElement = new Element(&symbol[0], &++_counter, &_UserId);
    AnswerLinePos positionElement = getPosition(position);

    AnswerForInsertAction answer;
    answer = insertElement(_insertElement, positionElement.line, positionElement.pos);

    return createCommand(false, _insertElement, answer.elementBeforeInsert, _insertElement->next);
};

std::string WorkWithLines::deleteElementFromPosition(size_t position) {
    AnswerLinePos pos = getPosition(position);

    return createCommand(true, deleteElementFromLineAndPos(pos.line, pos.pos).elementBeforeInsert);
};

std::string WorkWithLines::insertElementInPosition(std::string command) {
    Command com(command);

    insertElement(com._insertElement, com._beforeElement,com._afterElemenet);
    return command;
};

std::string WorkWithLines::deleteElementFromPosition(std::string command) {
    Command com(command);
    
    size_t position = 0;
    Element* nowEl = beggining;
    
    while (nowEl && !(nowEl->isVisible && checkForAfterElement(nowEl, com._insertElement))) {
        if (nowEl->isVisible) {
            position++;
        }
        nowEl = nowEl->next;
    }

    AnswerLinePos pos = getPosition(position);
    
    delete com._insertElement;
    
    return createCommand(true, deleteElementFromLineAndPos(pos.line, pos.pos).elementBeforeInsert);
};

size_t WorkWithLines::getQuantityOfLines() {
    return lineCount;
};

Element* WorkWithLines::getStartOfLine(size_t lineNumber) {
    if (!lines) {
        return nullptr;
    }

    if (lineNumber <= lineCount) {
        StartOfLine* searchForStart = searcher->getToLine(lines, lineNumber);
        
        return searchForStart->_elementStart;
    }
    return nullptr;
};


std::string WorkWithLines::createCommand(bool isDelete, Element* elementOperation, Element* beforeElement, Element* afterElement) {
    std::string firstPartOfCommand = std::to_string(elementOperation->count) + '|' + std::to_string(elementOperation->UserId);
    std::string returnCommand;

    if (isDelete) {
        // delete command
        
        returnCommand = "d:" + firstPartOfCommand + '|';
        return returnCommand;
    }
    
    size_t parts = 0;
    std::string beforeElementString = "";
    std::string afterElementString = "";

    if (afterElement) {
        afterElementString = std::to_string(afterElement->count) + '|' + std::to_string(afterElement->UserId) + ":";
        parts += 2;
    }

    if (beforeElement) {
        beforeElementString = std::to_string(beforeElement->count) + '|' + std::to_string(beforeElement->UserId) + ":";
        parts += 1;
    }

    returnCommand += "i:" + firstPartOfCommand + "|" + elementOperation->_value + ":" + beforeElementString + afterElementString + std::to_string(parts);
    return returnCommand;
};

AnswerForInsertAction WorkWithLines::insertElement(Element* insertElement, size_t lineWhereInsert, size_t positionWhereInsert) {
    AnswerForInsertAction answer;

    answer.elementBeforeInsert = nullptr;
    answer.quantOfElementsBefore = positionWhereInsert;
    answer.quantOfLine = lineWhereInsert;


    if (beggining != nullptr) {
        // elements exist
        StartOfLine* BeforeInsertLine = lines;

        if (lineWhereInsert > 0) {
            for (size_t i = 0; i < lineWhereInsert - 1; ++i) {
                BeforeInsertLine = BeforeInsertLine->next;
            }
        }

        if (positionWhereInsert == 0) {
            if (lineWhereInsert == 0) {
                Element* tmpEl = beggining;

                if (tmpEl->isVisible) {
                    insertElement->next = beggining;
                    beggining = insertElement;

                } else {
                    while (tmpEl->next && !tmpEl->next->isVisible) {
                        tmpEl = tmpEl->next;
                    }

                    insertElement->next = tmpEl->next;
                    tmpEl->next = insertElement;

                    answer.elementBeforeInsert = tmpEl;
                }

                lines->_elementStart = insertElement;
                lines->_sizeOfLine++;

            } else {
                // first symbol not first line

                Element* tmpElement = BeforeInsertLine->_elementStart;
                
                while (!(tmpElement->_value == '\n' && tmpElement->isVisible)) {
                    tmpElement = tmpElement->next;
                }
                
                if (BeforeInsertLine->next->_sizeOfLine == 0) {
                    delete BeforeInsertLine->next->_elementStart;
                }

                insertElement->next = tmpElement->next;
                tmpElement->next = insertElement;

                BeforeInsertLine->next->_sizeOfLine++;
                BeforeInsertLine->next->_elementStart = insertElement;   

                answer.elementBeforeInsert = tmpElement;             
            }
        } else {
            // not first element
            Element* tmpEl;
            StartOfLine* tmpLine;
            
            if (BeforeInsertLine->next) {
                tmpLine = BeforeInsertLine->next;
            } else {
                tmpLine = BeforeInsertLine;
            }

            tmpEl = tmpLine->_elementStart;

            tmpEl = searcher->getToPosition(tmpEl, positionWhereInsert);

            insertElement->next = tmpEl->next;
            tmpEl->next = insertElement;

            tmpLine->_sizeOfLine++;

            answer.elementBeforeInsert = tmpEl;
        }

    } else {
        beggining = insertElement;
        
        lines = new StartOfLine(insertElement, 1);
        lineCount++;
    }
    
    // Check for \n
    insertEnter(answer, insertElement);
    
    return answer;
};

AnswerLinePos WorkWithLines::getPosition(size_t position) {
    AnswerLinePos answer;
    StartOfLine* tmpLine = lines;
    
    while (tmpLine && position > tmpLine->_sizeOfLine) {
        answer.line++;
        
        position -= tmpLine->_sizeOfLine;
        tmpLine = tmpLine->next;
    }

    if (tmpLine && position == tmpLine->_sizeOfLine) {
        Element* tmpElement = tmpLine->_elementStart;
        size_t positionNow = 0;
        
        while(positionNow < position) {
            if (tmpElement->isVisible) {
                positionNow++;
                if (tmpElement->_value == '\n') {
                    answer.line++;
                    position -= positionNow;
                    break;
                }
            }
            tmpElement = tmpElement->next;
        }
    }

    answer.pos = position;

    return answer;
};

AnswerForInsertAction WorkWithLines::deleteElementFromLineAndPos(size_t lineWhereToDelete, size_t positionInLine) {
    AnswerForInsertAction answer;
    
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

                answer.elementBeforeInsert = deletionLine->_elementStart;

                deletionLine->_elementStart->isVisible = false;
                deletionElement = deletionLine->_elementStart;
            
                delete deletionLine;
            } else {
                // delete not from first line

                beforeDeletionLine->next = deletionLine->next;

                answer.elementBeforeInsert = deletionLine->_elementStart;

                deletionLine->_elementStart->isVisible = false;
                deletionElement = deletionLine->_elementStart;

                if (lineWhereToDelete == lineCount) {
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
            
            answer.elementBeforeInsert = deletionLine->_elementStart;
            
            deletionLine->_elementStart->isVisible = false;
            deletionLine->_elementStart = nextVisible;
            deletionLine->_sizeOfLine--;
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

        answer.elementBeforeInsert = tmp;

        tmp->isVisible = false;
        deletionLine->_sizeOfLine--;
    }

    if (deletionElement->_value == '\n' && !isDeleteLine) {
        
        StartOfLine* tmp = deletionLine->next;
        deletionLine->next = deletionLine->next->next;
        
        lineCount--;
        delete tmp;
    }
    
    // output command
    // first part of command
    
    return answer;
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

    delete searcher;
};

