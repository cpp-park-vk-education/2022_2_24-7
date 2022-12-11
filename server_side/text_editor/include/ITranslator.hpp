#include <string>

#include "element.hpp"

class ITranslator {
    virtual std::string returnStringFromDataType(Element* from) = 0;
};