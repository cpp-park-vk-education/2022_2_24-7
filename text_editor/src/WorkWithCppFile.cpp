#include "WorkWithFile.hpp"

bool WorkWithCppFile::addExtension(std::string extensionToAdd) {
    _extension = extensionToAdd;
    return 1;
};

bool WorkWithCppFile::addPathFile(std::string addPathToFile) {
    _path = addPathToFile;
    return 1;
};

bool WorkWithCppFile::writeToFile(std::string whatToWrite) {
    std::ofstream out;

    out.open(_path + "res" + _extension, std::ios::app);
    if (out.is_open())
    {
        out << whatToWrite;
    } else {
        return 0;
    }

    out.close();
    return 1;
};

bool WorkWithCppFile::clearFile() {
    std::remove((_path + "res" + _extension).c_str());
    return 1;
};

std::string WorkWithCppFile::getPath() {
    return _path + "res" + _extension;
};
