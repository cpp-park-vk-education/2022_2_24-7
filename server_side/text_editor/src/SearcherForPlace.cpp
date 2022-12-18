#include "SearcherForPlace.hpp"

bool checkForAfterElement(Element* afterElement, Element* checkElement) {
    if (!afterElement) {
        return 1;
    }
    return checkElement->count == afterElement->count && checkElement->UserId == afterElement->UserId;
};

bool checkForBeforeLess(Element* elementBefore, Element* elementAfter) {
    if (!elementBefore || !elementAfter) {
        return false;
    }
    return elementBefore->UserId < elementAfter->UserId;
};

AnswerForInsertAction Searcher::whatPositionDelete(Element* elementToDelete, Element* beggining, StartOfLine* lines) {
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


AnswerForInsertAction Searcher::whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line) {
    AnswerForInsertAction answer;
    StartOfLine* tmpLine = line;
    
    if (beforeInsert->next == nullptr) {
        if (beforeInsert->isVisible && beforeInsert->_value != '\n') {
            answer.elementBeforeInsert = beforeInsert;
            answer.quantOfElementsBefore = 1;
        }

        return answer;
    }

    if (checkForAfterElement(insertElement, beforeInsert->next) || checkForAfterElement(afterElement, beforeInsert->next)) {
        answer.quantOfElementsBefore = 1;
    }


    while (beforeInsert->next && checkForAfterElement(beforeInsert->next, insertElement) && !checkForAfterElement(afterElement, beforeInsert->next)) {
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

Element* Searcher::getToPosition(Element* fromWhere, size_t position) {
    Element* tmpElement = fromWhere;

    size_t elementPosition = 1;
    while (elementPosition < position) {
        tmpElement = tmpElement->next;

        if (tmpElement->isVisible) {
            elementPosition++;
        }
    }
    return tmpElement;
};
