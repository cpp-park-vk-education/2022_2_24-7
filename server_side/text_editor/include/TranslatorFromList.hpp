#pragma once
#include "ITranslator.hpp"

class TranslatorFromList : public ITranslator {
   public:
    std::string returnStringFromDataType(Element* from) override;

    ~TranslatorFromList() override = default;
};
