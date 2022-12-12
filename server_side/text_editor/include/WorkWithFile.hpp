#include "IWorkWithFile.hpp"

class WorkWithCppFile: public IWorkWithFile{
    public:
    bool addExtension(std::string extensionToAdd) override;
    bool addPathFile(std::string addPathToFile) override;
    
    bool writeToFile(std::string whatToWrite) override;
    std::string getPath() override;

    private:
    std::string _path;
    std::string _extension;
};