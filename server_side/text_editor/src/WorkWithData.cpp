// #include "../include/WorkWithData.hpp"
#include "WorkWithData.hpp"

WorkWithData::WorkWithData() {
    // translator = new TranslatorFromList;
    workWithCPP = new WorkWithCppFile;
    workWithLog = new WorkWithLogFile;
};

std::string WorkWithData::operationWithData(std::string operation, bool isCommand) {
    bool isInsert = false;
    
    std::vector<std::string> vecs = parseString(operation, ':');
    if (vecs[0][0] == 'i') {
        isInsert = true;
    }

    std::string stringToWriteInLogs;

    if (isCommand) {
        if (isInsert){
            stringToWriteInLogs = textEditor->insertElementInPosition(operation);
        } else {
            stringToWriteInLogs = textEditor->deleteElementFromPosition(operation);
        }
    } else {
        if (isInsert){
            size_t post = std::stoul(vecs[2]);

            stringToWriteInLogs = textEditor->insertElementInPosition(post, vecs[1]);
        } else {
            stringToWriteInLogs = textEditor->deleteElementFromPosition(std::stoul(vecs[1]));
        }
    }
    
    workWithLog->writeToFile(stringToWriteInLogs);
    
    return stringToWriteInLogs;
};

void WorkWithData::userFirst(size_t UserId, size_t userCount) {
    textEditor = new WorkWithLines(UserId, userCount);
};

std::string WorkWithData::getLine(size_t numberOfLine) {
    Element* tmp = textEditor->getStartOfLine(numberOfLine);
    std::string returnString;
    while (tmp && tmp->isVisible) {
        returnString.push_back(tmp->_value);
        
        if (tmp->_value == '\n') {
            break;
        }
        
        tmp = tmp->next;
    }
    return returnString;
};

void WorkWithData::addFile(std::string path) {
    workWithCPP->addExtension("cpp");
    workWithCPP->addPathFile(path);

    workWithLog->addExtension("txt");
    workWithLog->addPathFile(path);
};

std::string WorkWithData::getLogFileDirectory() {
    return workWithLog->getPath();
};

std::string WorkWithData::getFileWithDataDricetory() {
    workWithCPP->clearFile();
    
    for (size_t i = 0; i < textEditor->getQuantityOfLines(); ++i) {
        workWithCPP->writeToFile(getLine(i));
    }

    return workWithCPP->getPath();
};
