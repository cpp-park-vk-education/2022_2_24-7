#include "TranslatorFromList.hpp"

std::string TranslatorFromList::returnStringFromDataType(Element* from) {
    Element* tmp = from;
    std::string returnString;
    while (tmp) {
        if (tmp->isVisible) {
            returnString.push_back(tmp->_value);
            
            if (tmp->_value == '\n') {
                break;
            }
        }
        tmp = tmp->next;
    }
    return returnString;
};
