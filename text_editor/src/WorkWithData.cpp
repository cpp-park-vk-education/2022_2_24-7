// #include "../include/WorkWithData.hpp"
#include "WorkWithData.hpp"

WorkWithData::WorkWithData() {
    translator = new TranslatorFromList;
    workWithCPP = new WorkWithCppFile;
    workWithLog = new WorkWithLogFile;
};

std::string WorkWithData::operationWithData(std::string operation, bool isCommand) {
    bool isInsert = false;
    bool isDelete = false;
    
    std::vector<std::string> vecs = parseString(operation, ':');
    if (vecs[0][0] == 'i') {
        isInsert = true;
    }
    if (vecs[0][0] == 'd') {
        isDelete = true;
    }

    std::string stringToWriteInLogs;
    std::string stringToReturn;

    if (isCommand) {
        stringToWriteInLogs = operation;
        if (isInsert){
            stringToReturn = textEditor->insertElementInPosition(operation);
        } else if (isDelete) {
            stringToReturn = textEditor->deleteElementFromPosition(operation);
        }
        
        stringToWriteInLogs = operation;
    } else {
        if (isInsert){
            size_t post = std::stoul(vecs[2]);

            stringToWriteInLogs = textEditor->insertElementInPosition(post, vecs[1]);
        } else if (isDelete) {
            stringToWriteInLogs = textEditor->deleteElementFromPosition(std::stoul(vecs[1]));
        }

        stringToReturn = stringToWriteInLogs;

    }
    
    workWithLog->writeToFile(stringToWriteInLogs);
    
    return stringToReturn;
};

void WorkWithData::userFirst(size_t UserId, size_t userCount) {
    textEditor = new WorkWithLines(UserId, userCount);
};

std::string WorkWithData::getLine(size_t numberOfLine) {
    return translator->returnStringFromDataType(textEditor->getStartOfLine(numberOfLine));
};

void WorkWithData::addFile(std::string path) {
    workWithCPP->addExtension(".cpp");
    workWithCPP->addPathFile(path);

    workWithLog->addExtension(".txt");
    workWithLog->addPathFile(path);
};

std::string WorkWithData::getLogFileDirectory() {
    return workWithLog->getPath();
};

std::string WorkWithData::getFileWithDataDricetory() {
    workWithCPP->clearFile();
    
    for (size_t i = 0; i < textEditor->getQuantityOfLines(); ++i) {
        workWithCPP->writeToFile(translator->returnStringFromDataType(textEditor->getStartOfLine(i)));
    }

    return workWithCPP->getPath();
};


WorkWithData::~WorkWithData() {
    delete translator;
    delete workWithCPP;
    delete workWithLog;
    delete textEditor;
};
