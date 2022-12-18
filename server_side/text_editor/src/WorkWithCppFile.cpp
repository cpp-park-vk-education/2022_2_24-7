#include "WorkWithFile.hpp"

bool WorkWithCppFile::addExtension(std::string extensionToAdd) {
    _extension = extensionToAdd;
};

bool WorkWithCppFile::addPathFile(std::string addPathToFile) {
    _path = addPathToFile;
};

bool WorkWithCppFile::writeToFile(std::string whatToWrite) {
    // TODO write to file dont create file
    std::ofstream out;

    out.open(_path + "res" + _extension, std::ios::app);

    if (out.is_open())
    {
        out << whatToWrite << std::endl;
    }

    out.close();
};

bool WorkWithCppFile::clearFile() {
    std::remove((_path + "res" + _extension).c_str());
};

std::string WorkWithCppFile::getPath() {
    return _path + "res" + _extension;
};
