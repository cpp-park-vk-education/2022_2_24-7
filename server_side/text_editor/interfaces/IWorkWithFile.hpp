#pragma once
#include <string>

class IWorkWithFile {
    public:
    virtual bool addExtension(std::string extensionToAdd) = 0;
    virtual bool addPathFile(std::string addPathToFile) = 0;
    
    virtual bool writeToFile(std::string whatToWrite) = 0;
    virtual bool clearFile() = 0;

    virtual std::string getPath() = 0;

    virtual ~IWorkWithFile() = default;
};