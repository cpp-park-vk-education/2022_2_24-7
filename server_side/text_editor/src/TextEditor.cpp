// #include "TextEditor.hpp"
#include "../include/TextEditor.hpp"


bool funcWithBefore(Element* el, Element* el1) {
    if (el1)  {
        return el->count == el1->count && el1->UserId == el->UserId;
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
                afterThis->next->next = newLine->_elementStart;
                newLine->next = lines->next;
                lines->next = newLine;
            } else {
                // not first line
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
    Answer answerWhereElementBefore = searchForElement(beggining, com._afterElemenet,lines);

    if (beggining) {
        // elements exist
        if (lines) {
            searchForElement(answerWhereElementBefore, com, &lines, &beggining);
        } else {
            // lines doesnt exist
            Element* tmp = beggining;
            if (answerWhereElementBefore.answerElement) {
                tmp = answerWhereElementBefore.answerElement;
            }
            bool isSearch = false;
            while (tmp->next && tmp->next->UserId < com._insertElement->UserId && funcWithBefore(tmp->next, com._beforeElement)) {
                tmp = tmp->next;
                isSearch = true;
            }
            
            if (isSearch) {
                com._insertElement->next = tmp->next;
                tmp->next = com._insertElement;
            } else {
                if (answerWhereElementBefore.answerElement) {
                    com._insertElement->next = tmp->next;
                    tmp->next = com._insertElement;
                    
                    lines = new StartOfLine(com._insertElement, 1);
                } else {
                    insertBeforeFirstElement(com._insertElement, &beggining, &lines);
                }
            }
        }
    } else {
        // elements doens't exist
        beggining = com._insertElement;

        lines = new StartOfLine(com._insertElement, 1);
    }
    

    // insert after \n
    if (com._insertElement && com._insertElement->_value == '\n') {
        Element* tmp = com._insertElement;
        bool isNewLine = false;
        
        while (tmp && !tmp->isVisible) {
            if (tmp == answerWhereElementBefore.answerLine->next->_elementStart) {
                isNewLine = true;
                break;
            }
            tmp = tmp->next;
        }

        if (!(tmp && !isNewLine)) {
            StartOfLine* tmpCreatedLine = new StartOfLine();
            
            tmpCreatedLine->next = answerWhereElementBefore.answerLine->next;
            answerWhereElementBefore.answerLine->next = tmpCreatedLine;
        };
    }

    return command;
};

std::string WorkWithLines::deleteElementFromPosition(std::string command) {

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

    if (tmp->next) {
        while (tmp->next->UserId < com._beforeElement->UserId || funcWithBefore(tmp->next, com._beforeElement)) {
            if (tmp->_value == '\n' && tmp->isVisible) {
                answerWhereElementBefore.afterEnter = true;
            }

            if (tmpLine->_elementStart == tmp) {
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
            } else {
                tmpLine->_sizeOfLine++;
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

                } else {
                    beforeLine->_sizeOfLine++;
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
                } else {
                    tmpLine++;
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
                } else {
                    (*line)->_sizeOfLine++;
                }

            } else {
                // beggining userid more or equal then insert
                insertBeforeFirstElement(com._insertElement, begginng, line);
            }
        } else {
            // end of line
            com._insertElement->next = tmp->next;
            tmp->next = com._insertElement;

            if (answerWhereElementBefore.afterEnter) {
                if (answerWhereElementBefore.answerLine->next->_sizeOfLine == 0) {
                    delete answerWhereElementBefore.answerLine->next->_elementStart;
                }

                answerWhereElementBefore.answerLine->next->_elementStart = com._insertElement;
                answerWhereElementBefore.answerLine->next->_sizeOfLine++;
            } else {
                answerWhereElementBefore.answerLine->_sizeOfLine++;
            }

        }
    }
};

