#include "Functors.hpp"

bool checkForAfterElement(Element* afterElement, Element* checkElement) {
    return false;
};

bool checkForBeforeLess(Element* elementBefore, Element* elementAfter) {
    return false;
};

bool  checkForLess::func(Element* elementBefore, Element* elementAfter) {
    return false;
};

bool  checkForNotEqual::func(Element* elementBefore, Element* elementAfter) {
    return false;
};
