#include <string>

class IProject;

class ICommandAnalyzer {
    public:
    bool analyzeCommand(std::string command);
};

class CodeCommandAnalyzer : public ICommandAnalyzer {
    public:
    CodeCommandAnalyzer(IProject * parent) : _parent(parent) {};
    bool analyzeCommand(std::string command);
    
    private:
    IProject * _parent;
};