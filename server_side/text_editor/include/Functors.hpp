#pragma once
#include "element.hpp"

bool checkForAfterElement(Element* afterElement, Element* checkElement);
bool checkForBeforeLess(Element* elementBefore, Element* elementAfter);

struct IcheckForLessOrEqual {
    virtual bool func(Element* elementBefore, Element* elementAfter) = 0;
};

struct checkForLess : public IcheckForLessOrEqual {
    bool func(Element* elementBefore, Element* elementAfter) override;
};

struct checkForNotEqual : public IcheckForLessOrEqual {
    bool func(Element* elementBefore, Element* elementAfter) override;
};
