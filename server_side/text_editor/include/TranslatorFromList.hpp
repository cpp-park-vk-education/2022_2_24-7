#pragma once
#include "ITranslator.hpp"

class TranslatorFromList : public ITranslator {
    std::string returnStringFromDataType(Element* from) override;
};
