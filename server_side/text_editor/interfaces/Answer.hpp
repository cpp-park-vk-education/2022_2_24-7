#pragma once

#include "StartOfLine.hpp"
#include "element.hpp"

struct AnswerForInsertAction {
    AnswerForInsertAction()
        : quantOfElementsBefore(0), quantOfLine(0), elementBeforeInsert(nullptr), isEnterBefore(false){};

    size_t quantOfElementsBefore;
    size_t quantOfLine;

    Element* elementBeforeInsert;

    bool isEnterBefore;
};

struct AnswerLinePos {
    AnswerLinePos() : line(0), pos(0){};

    size_t line;
    size_t pos;
};

struct AnswerForLineAndElementVisible {
    AnswerForLineAndElementVisible() : lineCount(0), visibleCount(0), line(nullptr), element(nullptr){};

    size_t lineCount;
    size_t visibleCount;

    StartOfLine* line;
    Element* element;
};
