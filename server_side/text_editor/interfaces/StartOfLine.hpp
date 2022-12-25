#pragma once
#include "element.hpp"

struct StartOfLine {
    StartOfLine(Element* element = nullptr, const size_t sizeOfLine = 0) {
        _elementStart = element;
        _sizeOfLine = sizeOfLine;
        next = nullptr;

        if (!element) {
            size_t a = 0;
            char sym = 'x';
            _elementStart = new Element(&sym, &a, &a);
        }
    };

    Element* _elementStart;
    size_t _sizeOfLine;

    StartOfLine* next;
};
