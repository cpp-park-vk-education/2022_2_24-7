#pragma once
#include "ISearchForPlace.hpp"
#include "TextEditor.hpp"


bool checkForAfterElement(Element* afterElement, Element* checkElement);
bool checkForBeforeLess(Element* elementBefore, Element* elementAfter);


class Searcher : public ISearchForPlace {
    public:
    AnswerForInsertAction whatPositionDelete(Element* elementToDelete, Element* beggining, StartOfLine* lines) override;
    AnswerForInsertAction whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line) override;

    Element* getToPosition(Element* fromWhere, size_t position) override;
};