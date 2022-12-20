#pragma once
#include "IWorkWithFile.hpp"

#include <iostream>
#include <fstream>

class WorkWithLogFile: public IWorkWithFile{
    public:
    bool addExtension(std::string extensionToAdd) override;
    bool addPathFile(std::string addPathToFile) override;
    
    bool writeToFile(std::string whatToWrite) override;
    bool clearFile() override;

    std::string getPath() override;

    ~WorkWithLogFile() override = default;

    private:
    std::string _path;
    std::string _extension;
};
