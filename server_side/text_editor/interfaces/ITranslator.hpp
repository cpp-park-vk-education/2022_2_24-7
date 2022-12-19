#pragma once
#include <string>

#include "element.hpp"

class ITranslator {
    public:
    virtual std::string returnStringFromDataType(Element* from) = 0;

    virtual ~ITranslator() = default;
};