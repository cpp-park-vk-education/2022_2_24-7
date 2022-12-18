#pragma once
#include "element.hpp"

struct AnswerForInsertAction {
    AnswerForInsertAction() : quantOfElementsBefore(0) , quantOfLine(0), elementBeforeInsert(nullptr), isEnterBefore(false) {};

    size_t quantOfElementsBefore;
    size_t quantOfLine;
    
    Element* elementBeforeInsert;
    
    bool isEnterBefore;
};
