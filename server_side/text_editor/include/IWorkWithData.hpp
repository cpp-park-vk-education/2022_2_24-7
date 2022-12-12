#pragma once
#include <string>

class IWorkWithData {
    public:
    virtual std::string operationWithData(std::string operation, bool isCommand = false) = 0; // If do on server then isCommand set True
    virtual void userFirst(size_t UserId = 0, size_t userCount = 0) = 0;

    virtual std::string getLine(size_t numberOfLine) = 0;
    
    virtual void addFile(std::string path) = 0;
    virtual std::string getLogFileDirectory() = 0;
    virtual std::string getFileWithDataDricetory() = 0;
};