#include "WorkWithLogFile.hpp"

bool WorkWithLogFile::addExtension(std::string extensionToAdd) {
    _extension = extensionToAdd;
    return 1;
};

bool WorkWithLogFile::addPathFile(std::string addPathToFile) {
    _path = addPathToFile;
    return 1;
};

bool WorkWithLogFile::writeToFile(std::string whatToWrite) {
    std::ofstream out;

    out.open(_path + "log" + _extension, std::ios::app);

    if (out.is_open())
    {
        out << whatToWrite << "!!" << std::endl;
    } else {
        return 0;
    }

    out.close();
    return 1;
};

bool WorkWithLogFile::clearFile() {
    std::remove((_path + "log" + _extension).c_str());
    return 1;
};

std::string WorkWithLogFile::getPath() {
    return _path + "res" + _extension;
};
