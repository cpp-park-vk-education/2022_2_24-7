#include <string>

#include "element.hpp"

class IWorkWithText;

class ISearchForPlace {
    public:
    virtual std::string findWhereToPlace(Element* elementToPlace) = 0;
};