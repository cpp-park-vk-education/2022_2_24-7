#include "WorkWithLogFile.hpp"

bool WorkWithLogFile::addExtension(std::string extensionToAdd) {
    _extension = extensionToAdd;
};

bool WorkWithLogFile::addPathFile(std::string addPathToFile) {
    _path = addPathToFile;
};

bool WorkWithLogFile::writeToFile(std::string whatToWrite) {
    // TODO write to file dont create file
    std::ofstream out;

    out.open(_path + "log" + _extension, std::ios::app);

    if (out.is_open())
    {
        out << whatToWrite << "!!" << std::endl;
    }

    out.close();
};

bool WorkWithLogFile::clearFile() {
    std::remove((_path + "log" + _extension).c_str());
};

std::string WorkWithLogFile::getPath() {
    return _path + "res" + _extension;
};
