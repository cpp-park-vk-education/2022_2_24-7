#pragma once
#include <string>

#include "element.hpp"
#include "Answer.hpp"
#include "StartOfLine.hpp"
#include "Functors.hpp"


class ISearchForPlace {
    public:

    virtual AnswerForInsertAction whatPositionDelete(Element* elementToDelete, Element* beggining, StartOfLine* lines) = 0;
    virtual AnswerForInsertAction whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line) = 0;

    virtual Element* getToPosition(Element* fromWhere, size_t position) = 0;
    virtual StartOfLine* getToLine(StartOfLine* line, size_t numberOfLine) = 0;

    virtual Element* getToEndOfLine(Element* start) = 0;
    virtual Element* skipInvisibleElements(Element* start) = 0;

    virtual AnswerForLineAndElementVisible searchForLineAndPos(Element* start, Element* compareElement, StartOfLine* line, IcheckForLessOrEqual* func) = 0;

    virtual ~ISearchForPlace() = default;
};
