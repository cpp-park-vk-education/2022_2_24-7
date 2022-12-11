// #include "TextEditor.hpp"
#include "../include/TextEditor.hpp"

struct Answer {
    Answer() : answerElement(nullptr), answerLine(nullptr), linePos(0), afterEnter(false) {};

    Element * answerElement;
    StartOfLine* answerLine;
    size_t linePos;

    bool afterEnter;
};

WorkWithLines::WorkWithLines(size_t UserId, size_t counter) :  lineCount(0), _counter(counter), _UserId(UserId) {
    // searcher = new Searcher(this);
    lines = nullptr;
    beggining = nullptr;
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

            if (tmp->count == whatSearch->count && tmp->UserId == whatSearch->UserId) {
                break;
            }

            if (line && line->_elementStart == tmp) {
                beforeLine = line;
                line = line->next;
                lineCount++;
                enter = false;
            }

            tmp = tmp->next;
        }

        if (line && line->_elementStart == tmp) {
            beforeLine = line;
            line = line->next;
            lineCount++;
            enter = false;
        }

        answer.answerElement = tmp;
        answer.answerLine = beforeLine;
        answer.linePos = lineCount;
        answer.afterEnter = enter;

        return answer;
    }
    
    return answer;
}

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
            // lines exist

            if (answerWhereElementBefore.linePos == 0) {
                // insert before first line
                // TODO same methods with one difference in input params below

                if (answerWhereElementBefore.answerElement) {
                    // element before insert exist
                    if (com._beforeElement) {
                        // element after insert exist
                        Element* tmp = answerWhereElementBefore.answerElement;
                        StartOfLine* tmpLine = lines;
                        StartOfLine* beforeLine = nullptr;
                        
                        while (tmp->next->UserId < com._insertElement->UserId || !(tmp->next->count == com._beforeElement->count && tmp->next->UserId == com._beforeElement->UserId)) {
                            if (tmp == tmpLine->_elementStart) {
                                // if pass line start
                                beforeLine = tmpLine;
                                tmpLine = tmpLine->next;
                                answerWhereElementBefore.afterEnter = false;
                            }

                            if (tmp->_value == '\n' && tmp->isVisible) {
                                answerWhereElementBefore.afterEnter = true;
                            }

                            tmp = tmp->next;
                        }

                        if (beforeLine) {
                            // in first line or later
                            com._insertElement->next = tmp->next;
                            tmp->next = com._insertElement;

                            if( answerWhereElementBefore.afterEnter) {
                                // after enter input
                                beforeLine->next->_sizeOfLine++;
                                beforeLine->next->_elementStart = com._insertElement;
                            } else {
                                // not after enter input
                                beforeLine->_sizeOfLine++;
                            }
                            
                        } else {
                            // before first line
                            com._insertElement->next = tmp->next;
                            tmp->next = com._insertElement;
                            
                            lines->_elementStart = com._insertElement;
                            lines->_sizeOfLine++;
                        }

                    } else {
                        // element before insert doesnt exist
                        Element* tmp = answerWhereElementBefore.answerElement;
                        StartOfLine* tmpLine = lines;
                        StartOfLine* beforeLine = nullptr;
                        
                        while (tmp->next->UserId < com._insertElement->UserId) {
                            if (tmp == tmpLine->_elementStart) {
                                // if pass line start
                                beforeLine = tmpLine;
                                tmpLine = tmpLine->next;

                                answerWhereElementBefore.afterEnter = false;
                            }

                            if (tmp->_value == '\n' && tmp->isVisible) {
                                answerWhereElementBefore.afterEnter = true;
                            }


                            tmp = tmp->next;
                        }

                        if (beforeLine) {
                            // in first line or later
                            com._insertElement->next = tmp->next;
                            tmp->next = com._insertElement;
                            
                            if( answerWhereElementBefore.afterEnter) {
                                // after enter input
                                beforeLine->next->_sizeOfLine++;
                                beforeLine->next->_elementStart = com._insertElement;
                            } else {
                                // not after enter input
                                beforeLine->_sizeOfLine++;
                            }
                            
                        } else {
                            // before first line
                            com._insertElement->next = tmp->next;
                            tmp->next = com._insertElement;
                            
                            lines->_elementStart = com._insertElement;
                            lines->_sizeOfLine++;
                        }
                    }

                } else {
                    // element after insert doesn't exist

                    if (com._beforeElement) {
                        // element before insert exist
                        Element* tmp = beggining;
                        StartOfLine* tmpLine = lines;
                        StartOfLine* beforeLine = nullptr;
                        bool flag = 1;
                        
                        while (tmp->next->UserId < com._insertElement->UserId || !(tmp->next->count == com._beforeElement->count && tmp->next->UserId == com._beforeElement->UserId)) {
                            if (tmp == tmpLine->_elementStart) {
                                // if pass line start
                                beforeLine = tmpLine;
                                tmpLine = tmpLine->next;
                            }

                            tmp = tmp->next;
                            flag = 0;
                        }

                        if (beforeLine) {
                            // in first line or later
                            com._insertElement->next = tmp->next;
                            tmp->next = com._insertElement;
                            
                            beforeLine->_sizeOfLine++;
                        } else {
                            // before first line
                            if (flag) {
                                // after beggining
                                com._insertElement->next = tmp->next;
                                tmp->next = com._insertElement;
                            } else {
                                // before beggining
                                com._insertElement->next = beggining;
                                beggining = com._insertElement;
                            }
                            
                            lines->_elementStart = com._insertElement;
                            lines->_sizeOfLine++;
                        }
                        

                    } else {
                        // element before insert doesnt exist
                        Element* tmp = beggining;
                        StartOfLine* tmpLine = lines;
                        StartOfLine* beforeLine = nullptr;
                        bool flag = 1;
                        
                        while (tmp->next->UserId < com._insertElement->UserId) {
                            if (tmp == tmpLine->_elementStart) {
                                // if pass line start
                                beforeLine = tmpLine;
                                tmpLine = tmpLine->next;
                            }

                            tmp = tmp->next;
                            flag = 0;
                        }

                        if (beforeLine) {
                            // in first line or later
                            com._insertElement->next = tmp->next;
                            tmp->next = com._insertElement;
                            
                            beforeLine->_sizeOfLine++;
                        } else {
                            // before first line
                            if (flag) {
                                // after beggining
                                com._insertElement->next = tmp->next;
                                tmp->next = com._insertElement;
                            } else {
                                // before beggining
                                com._insertElement->next = beggining;
                                beggining = com._insertElement;
                            }
                            
                            lines->_elementStart = com._insertElement;
                            lines->_sizeOfLine++;
                        }
                    }
                }
            } else {
                // insert not before first line
                if (com._beforeElement) {
                    // element after insert exist
                    Element* tmp = answerWhereElementBefore.answerElement;
                    StartOfLine* tmpLine = answerWhereElementBefore.answerLine;
                    StartOfLine* beforeLine = nullptr;
                    
                    while (tmp->UserId < com._insertElement->UserId || !(tmp->next->count == com._beforeElement->count && tmp->next->UserId == com._beforeElement->UserId)) {
                        if (tmp == tmpLine->_elementStart) {
                            // if pass line start
                            beforeLine = tmpLine;
                            tmpLine = tmpLine->next;
                            answerWhereElementBefore.afterEnter = false;
                        }

                        if (tmp->_value == '\n' && tmp->isVisible) {
                            answerWhereElementBefore.afterEnter = true;
                        }

                        tmp = tmp->next;
                    }

                    if (beforeLine) {
                        // in first line or later
                        com._insertElement->next = tmp->next;
                        tmp->next = com._insertElement;

                        if( answerWhereElementBefore.afterEnter) {
                            // after enter input
                            beforeLine->next->_sizeOfLine++;
                            beforeLine->next->_elementStart = com._insertElement;
                        } else {
                            // not after enter input
                            beforeLine->_sizeOfLine++;
                        }
                        
                    } else {
                        // before first line
                        com._insertElement->next = tmp->next;
                        tmp->next = com._insertElement;
                        
                        answerWhereElementBefore.answerLine->_elementStart = com._insertElement;
                        answerWhereElementBefore.answerLine->_sizeOfLine++;
                    }

                } else {
                    // element before insert doesnt exist
                    Element* tmp = answerWhereElementBefore.answerElement;
                    StartOfLine* tmpLine = answerWhereElementBefore.answerLine;
                    StartOfLine* beforeLine = nullptr;
                    
                    while (tmp->UserId < com._insertElement->UserId) {
                        if (tmp == tmpLine->_elementStart) {
                            // if pass line start
                            beforeLine = tmpLine;
                            tmpLine = tmpLine->next;

                            answerWhereElementBefore.afterEnter = false;
                        }

                        if (tmp->_value == '\n' && tmp->isVisible) {
                            answerWhereElementBefore.afterEnter = true;
                        }


                        tmp = tmp->next;
                    }

                    if (beforeLine) {
                        // in first line or later
                        com._insertElement->next = tmp->next;
                        tmp->next = com._insertElement;
                        
                        if( answerWhereElementBefore.afterEnter) {
                            // after enter input
                            beforeLine->next->_sizeOfLine++;
                            beforeLine->next->_elementStart = com._insertElement;
                        } else {
                            // not after enter input
                            beforeLine->_sizeOfLine++;
                        }
                        
                    } else {
                        // before first line
                        com._insertElement->next = tmp->next;
                        tmp->next = com._insertElement;
                        
                        answerWhereElementBefore.answerLine->_elementStart = com._insertElement;
                        answerWhereElementBefore.answerLine->_sizeOfLine++;
                    }
                }

            }

        } else {
            // lines doesnt exist
            lines = new StartOfLine(com._insertElement, 1);

            if (answerWhereElementBefore.answerElement) {
                // insert after element

                if (com._beforeElement) {
                    // insert before this element
                    Element* tmp = answerWhereElementBefore.answerElement;
                    StartOfLine* tmpLine = lines;
                    StartOfLine* beforeLine = nullptr;
                    
                    while (tmp->next->UserId < com._insertElement->UserId || !(tmp->next->count == com._beforeElement->count && tmp->next->UserId == com._beforeElement->UserId)) {
                        tmp = tmp->next;
                    }

                    com._insertElement->next = tmp->next;
                    tmp->next = com._insertElement;

                    lines = new StartOfLine(com._insertElement, 1);
                } else {
                    // insert after element somwehere
                    Element* tmp = answerWhereElementBefore.answerElement;
                    StartOfLine* tmpLine = lines;
                    StartOfLine* beforeLine = nullptr;
                    
                    while (tmp->next->UserId < com._insertElement->UserId) {
                        tmp = tmp->next;
                    }

                    com._insertElement->next = tmp->next;
                    tmp->next = com._insertElement;

                    lines = new StartOfLine(com._insertElement, 1);
                }
            } else {
                // insert into beggining

                if (com._beforeElement) {
                    // insert before this element
                    Element* tmp = beggining;
                    StartOfLine* tmpLine = lines;
                    StartOfLine* beforeLine = nullptr;
                    
                    while (tmp->next->UserId < com._insertElement->UserId || !(tmp->next->count == com._beforeElement->count && tmp->next->UserId == com._beforeElement->UserId)) {
                        tmp = tmp->next;
                    }

                    com._insertElement->next = tmp->next;
                    tmp->next = com._insertElement;

                    lines = new StartOfLine(com._insertElement, 1);
                } else {
                    // insert after element somwehere
                    Element* tmp = beggining;
                    StartOfLine* tmpLine = lines;
                    StartOfLine* beforeLine = nullptr;
                    
                    while (tmp->next->UserId < com._insertElement->UserId) {
                        tmp = tmp->next;
                    }

                    com._insertElement->next = tmp->next;
                    tmp->next = com._insertElement;

                    lines = new StartOfLine(com._insertElement, 1);
                }
            }
        }
    } else {
        // elements doens't exist
        beggining = com._insertElement;

        lines = new StartOfLine(com._insertElement, 1);
    }
    

    // insert after \n
    if (com._afterElemenet && com._afterElemenet->_value == '\n') {
        
        if (com._insertElement->next != nullptr) {}
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


bool funcWithBefore(Element* el, Element* el1) {
    if (el1)  {
        return el->count == el1->count && el1->UserId == el->UserId;
    } else {
        return true;
    }
}

void searchForElement(Answer& answerWhereElementBefore, Command& com, StartOfLine* line, Element* begginng) {
    Element* tmp = begginng;
    if (answerWhereElementBefore.answerElement) {
        tmp = answerWhereElementBefore.answerElement;
    }

    StartOfLine* tmpLine = line;
    StartOfLine* beforeLine = nullptr;
    bool flag = true;

    while (tmp->next->UserId < com._beforeElement->UserId || funcWithBefore(tmp->next, com._beforeElement)) {
        if (tmp->_value == '\n' && tmp->isVisible) {
            answerWhereElementBefore.afterEnter = true;
        }

        if (tmpLine->_elementStart == tmp) {
            beforeLine = tmpLine;
            tmpLine = tmpLine->next;
            
            answerWhereElementBefore.afterEnter = false;
        }

        flag = false;
        tmp = tmp->next;
    }

    if (beforeLine) {
        
        com._insertElement->next = tmp->next;
        tmp->next = com._insertElement;

        if (answerWhereElementBefore.afterEnter) {
            beforeLine->next->_sizeOfLine++;
            beforeLine->next->_elementStart = com._insertElement;
        } else {
            beforeLine->_sizeOfLine++;
        }
    } else {
        if (tmp == begginng && !flag) {
            
        }
        com._insertElement->next = tmp->next;
        tmp->next = com._insertElement;

        line->_elementStart = com._insertElement;
        line->_sizeOfLine++;
    }

}
