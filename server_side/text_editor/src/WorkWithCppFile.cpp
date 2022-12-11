#include "WorkWithFile.hpp"

bool WorkWithCppFile::addExtension(std::string extensionToAdd) {
    _extension = extensionToAdd;
};

bool WorkWithCppFile::addPathFile(std::string addPathToFile) {
    _path = addPathToFile;
};

bool WorkWithCppFile::writeToFile(std::string whatToWrite) {
    // TODO write to file dont create file
};

std::string WorkWithCppFile::getPath() {
    return _path;
};
