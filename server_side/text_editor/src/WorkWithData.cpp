// #include "../include/WorkWithData.hpp"
#include "WorkWithData.hpp"

WorkWithData::WorkWithData() {
    // translator = new TranslatorFromList;
    // workWithCPP = new WorkWithCppFile;
};

std::string WorkWithData::operationWithData(std::string operation, bool isCommand) {
    bool isInsert = false;
    std::vector<std::string> vecs = parseString(operation, ':');
    if (vecs[0][0] == 'i') {
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
            AnswerLinePos answ;
            size_t post = std::stoul(vecs[2]);
            textEditor->getLinePosFromPos(post);
            return textEditor->insertElementInPosition(answ.line, answ.pos, &vecs[1][0]);
        } else {
            AnswerLinePos answ;
            textEditor->getLinePosFromPos(std::stoul(vecs[1]));
            return textEditor->deleteElementFromPosition(answ.line,answ.pos);
        }
    }
};

void WorkWithData::userFirst(size_t UserId, size_t userCount) {
    textEditor = new WorkWithLines(UserId, userCount);
};

std::string WorkWithData::getLine(size_t numberOfLine) {
    // return translator->returnStringFromDataType(textEditor->getStartOfLine(numberOfLine));
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
    // workWithCPP->addExtension("cpp");
    // workWithCPP->addPathFile(path);
};

std::string WorkWithData::getLogFileDirectory() {
    // TODO
};

std::string WorkWithData::getFileWithDataDricetory() {
    // TODO
};
