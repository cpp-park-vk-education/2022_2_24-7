#pragma once

#include <string>

class IWorkWithData {
    virtual std::string operationWithData(std::string, bool) = 0;
    virtual void userFirst(size_t, size_t) = 0;
    virtual std::string getLine(size_t) = 0;
    virtual void addDirectoryToPlaceFiles(
        std::string) = 0;  // сюда я передаю путь до срр файла,
    virtual void addFile(std::string) = 0;  // с которым работают клиенты
    virtual std::string getLogFileDirectory() = 0;
    virtual std::string getFileWithDataDirectory() = 0;
};
