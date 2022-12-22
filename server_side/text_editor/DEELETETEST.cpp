#include "WorkWithData.hpp"
#include <vector>
#include <string>

int main() {
    // WorkWithData a;
    // a.userFirst(0,0);
    // a.addFile("");

    // std::cout << a.operationWithData("i:a:0") << std::endl;
    // a.operationWithData("i:b:1");
    // a.operationWithData("i:\n:1");
    // std::cout << a.operationWithData("i:4|0|x:1|0:2|0:3", 1) << std::endl;

    // a.operationWithData("d:0");
    // a.getFileWithDataDricetory();

    WorkWithData a;
    a.userFirst(0,0);

    std::vector<std::string> commands;
    commands.push_back("i:a:0");
    commands.push_back("i:b:1");
    commands.push_back("i:c:2");
    commands.push_back("i:d:3");
    commands.push_back("i:e:4");

    commands.push_back("i:f:5");
    commands.push_back("i:h:6");
    commands.push_back("i:h:7");
    commands.push_back("d:6");
    commands.push_back("d:5");

    commands.push_back("d:4");
    commands.push_back("d:3");
    commands.push_back("d:2");
    commands.push_back("d:1");
    commands.push_back("i:\n:2");

    commands.push_back("i:\n:3");
    commands.push_back("d:2");
    commands.push_back("d:1");
    commands.push_back("i:\n:2");
    commands.push_back("i:\n:3");
    
    commands.push_back("i:\n:4");
    commands.push_back("d:3");
    commands.push_back("d:2");
    commands.push_back("d:1");
    commands.push_back("i:y:2");

    size_t j = 0;
    for (auto i: commands) {
        a.operationWithData(i);
    }

    // a.operationWithData("i:a:0");
    // a.operationWithData("i:b:1");
    // a.operationWithData("i:\n:1");

    // a.operationWithData("d:0");
    std::cout << a.getLine(0) << std::endl; 
    std::cout << a.getLine(1) << std::endl;
    std::cout << a.getLine(2) << std::endl;
    

    return 0;
}