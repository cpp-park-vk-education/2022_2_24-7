#include "WorkWithData.hpp"

WorkWithData::WorkWithData() {
    translator = new TranslatorFromList;
    workWithCPP = new WorkWithCppFile;
};

std::string WorkWithData::operationWithData(std::string operation, bool isCommand = false) {
    bool isInsert = false;
    if (parseString(operation, ':')[0][0] == 'i') {
        isInsert = true;
    }

    if (isCommand) {
        if (isInsert){
            return textEditor->insertElementInPosition(operation);
        } else {
            return textEditor->deleteElementFromPosition(operation);
        }
    } else {
        // TODO
        if (isInsert){
            // return textEditor->insertElementInPosition();
        } else {
            // return textEditor->deleteElementFromPosition(operation);
        }
    }
};

void WorkWithData::userFirst(size_t UserId = 0, size_t userCount = 0) {
    textEditor = new WorkWithLines(UserId, userCount);
};

std::string WorkWithData::getLine(size_t numberOfLine) {
    return translator->returnStringFromDataType(textEditor->getStartOfLine(numberOfLine));
};

void WorkWithData::addFile(std::string path) {
    workWithCPP->addExtension("cpp");
    workWithCPP->addPathFile(path);
};

std::string WorkWithData::getLogFileDirectory() {
    // TODO
};

std::string WorkWithData::getFileWithDataDricetory() {
    
};
