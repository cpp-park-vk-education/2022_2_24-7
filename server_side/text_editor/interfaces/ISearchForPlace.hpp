#pragma once
#include <string>

#include "element.hpp"
#include "Answer.hpp"
#include "StartOfLine.hpp"

class ISearchForPlace {
    public:

    virtual AnswerForInsertAction whatPositionDelete(Element* elementToDelete, Element* beggining, StartOfLine* lines) = 0;
    virtual AnswerForInsertAction whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line) = 0;
};