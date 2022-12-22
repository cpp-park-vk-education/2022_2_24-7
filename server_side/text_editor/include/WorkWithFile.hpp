#pragma once
#include "IWorkWithFile.hpp"

#include <iostream>
#include <fstream>

class WorkWithCppFile: public IWorkWithFile{
    public:
    bool addExtension(std::string extensionToAdd) override;
    bool addPathFile(std::string addPathToFile) override;
    
    bool writeToFile(std::string whatToWrite) override;
    bool clearFile() override;

    std::string getPath() override;

    virtual ~WorkWithCppFile() = default;

    private:
    std::string _path;
    std::string _extension;
};
