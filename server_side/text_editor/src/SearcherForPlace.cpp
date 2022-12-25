#include "SearcherForPlace.hpp"

AnswerForInsertAction Searcher::whatPositionDelete(Element* elementToDelete, Element* beggining,
                                                   StartOfLine* lines) {
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

AnswerForInsertAction Searcher::whatPosition(Element* beforeInsert, Element* insertElement,
                                             Element* afterElement, StartOfLine* line) {
    AnswerForInsertAction answer;
    StartOfLine* tmpLine = line;

    if (beforeInsert->next == nullptr) {
        if (beforeInsert->isVisible && beforeInsert->_value != '\n') {
            answer.elementBeforeInsert = beforeInsert;
            answer.quantOfElementsBefore = 1;
        }

        return answer;
    }

    if (checkForAfterElement(insertElement, beforeInsert->next) ||
        checkForAfterElement(afterElement, beforeInsert->next)) {
        answer.quantOfElementsBefore = 1;
    }

    while (beforeInsert->next && checkForAfterElement(beforeInsert->next, insertElement) &&
           !checkForAfterElement(afterElement, beforeInsert->next)) {
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

StartOfLine* Searcher::getToLine(StartOfLine* line, size_t numberOfLine) {
    StartOfLine* insertLine = line;

    for (size_t i = 0; i < numberOfLine; i++) {
        insertLine = insertLine->next;
    }

    return insertLine;
};

Element* Searcher::getToEndOfLine(Element* start) {
    Element* before = start;
    while (before && !(before->isVisible && before->_value == '\n')) {
        before = before->next;
    }
    return before;
};

Element* Searcher::skipInvisibleElements(Element* start) {
    Element* before = start;
    while (before->next && !before->next->isVisible) {
        before = before->next;
    }
    return before;
};

AnswerForLineAndElementVisible Searcher::searchForLineAndPos(Element* start, Element* compareElement,
                                                             StartOfLine* line, IcheckForLessOrEqual* func) {
    AnswerForLineAndElementVisible answer;

    Element* tmpBefore = start;
    StartOfLine* tmpLine = line;

    while (tmpBefore && func->func(tmpBefore, compareElement)) {
        if (tmpBefore->isVisible) {
            answer.visibleCount++;

            if (tmpBefore->_value == '\n') {
                answer.lineCount++;
                answer.visibleCount = 0;

                tmpLine = tmpLine->next;
            }
        }
        tmpBefore = tmpBefore->next;
    }

    if (tmpBefore && tmpLine && tmpBefore->_value == '\n') {
        answer.lineCount++;
        answer.visibleCount = 0;

        tmpLine = tmpLine->next;
    }

    answer.element = tmpBefore;
    answer.line = tmpLine;

    return answer;
};
