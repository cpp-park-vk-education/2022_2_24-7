// #include "TextEditor.hpp"
#include "../include/TextEditor.hpp"

WorkWithLines::WorkWithLines(size_t UserId, size_t counter) :  lineCount(0), _counter(counter), _UserId(UserId) {
    // searcher = new Searcher(this);
    lines = nullptr;
    beggining = nullptr;
};

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
            for (size_t i = 0; i < lineWhereToPlace - 1; ++i) {
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

        if (positionInLine == 1) {
            searchElementBefore = searchElementBefore->next;
        }

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
            
            if (lineWhereToDelete == 0) {
                // delete from first line
                lines = lines->next;
                
                deletionLine->_elementStart->isVisible = false;
                delete deletionLine;
            } else {
                // delete not from first line
        
                beforeDeletionLine->next = deletionLine->next;

                deletionLine->_elementStart->isVisible = false;
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
        deletionElement = tmp;

        tmp->isVisible = false;
    }

    if (deletionElement->_value == '\n' && !isDeleteLine) {
        // ERROR can be error
        
        StartOfLine* tmp = deletionLine->next;
        deletionLine->next = deletionLine->next->next;
        
        delete tmp;
    }
    
    // output command
    // first part of command
    std::string firstPartOfCommand = std::to_string(_counter) + '|' + std::to_string(_UserId) + '|' ;

    std::string commandToReturn = "d:" + firstPartOfCommand;

    return commandToReturn;
};

std::string WorkWithLines::insertElementInPosition(std::string command) {

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
