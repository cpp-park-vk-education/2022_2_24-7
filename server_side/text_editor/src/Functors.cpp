#include "Functors.hpp"

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

bool checkForLess::func(Element* elementBefore, Element* elementAfter) {
    return checkForBeforeLess(elementBefore, elementAfter);
};

bool checkForNotEqual::func(Element* elementBefore, Element* elementAfter) {
    return !checkForAfterElement(elementBefore, elementAfter);
};
