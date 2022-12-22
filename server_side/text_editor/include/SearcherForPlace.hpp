#pragma once
#include "ISearchForPlace.hpp"
#include "TextEditor.hpp"


class Searcher : public ISearchForPlace {
    public:
    AnswerForInsertAction whatPositionDelete(Element* elementToDelete, Element* beggining, StartOfLine* lines) override;
    AnswerForInsertAction whatPosition(Element* beforeInsert, Element* insertElement, Element* afterElement, StartOfLine* line) override;

    Element* getToPosition(Element* fromWhere, size_t position) override;

    StartOfLine* getToLine(StartOfLine* line, size_t numberOfLine) override;
    
    Element* getToEndOfLine(Element* start) override;

    Element* skipInvisibleElements(Element* start) override;

    AnswerForLineAndElementVisible searchForLineAndPos(Element* start, Element* compareElement, StartOfLine* line, IcheckForLessOrEqual* func) override;

    virtual ~Searcher() = default;
};
