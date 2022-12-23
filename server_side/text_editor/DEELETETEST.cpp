#include "WorkWithData.hpp"
#include <vector>
#include <string>

int main() {
    WorkWithData a;
    a.userFirst(0,0);

    std::vector<std::string> commands;
    commands.push_back("i:a:0"); // a
    commands.push_back("i:b:1"); // ab
    commands.push_back("i:c:2"); // abc
    commands.push_back("i:d:3"); // abcd
    commands.push_back("i:e:4"); // abcde

    commands.push_back("i:f:5"); // abcdef
    commands.push_back("i:h:6"); // abcdefh
    commands.push_back("i:h:7"); // abcdefhh
    commands.push_back("d:6"); // abcdefh
    commands.push_back("d:5"); // abcdeh

    commands.push_back("d:4"); // abcdh
    commands.push_back("d:3"); // abch
    commands.push_back("d:2"); // abh
    commands.push_back("d:1"); // ah
    commands.push_back("i:\n:2"); // ah\n

    commands.push_back("i:\n:3"); // ah\n\n
    commands.push_back("d:2"); // ah\n
    commands.push_back("d:1"); // a\n
    commands.push_back("i:\n:2"); // a\n\n
    commands.push_back("i:\n:3"); // a\n\n\n
    
    commands.push_back("i:\n:4"); // a\n\n\n\n
    commands.push_back("d:3"); // a\n\n\n
    commands.push_back("d:2"); // a\n\n
    commands.push_back("d:1"); // a\n
    commands.push_back("i:y:2"); // a\ny

    size_t j = 0;
    for (auto i: commands) {
        a.operationWithData(i);
    }

    // std::cout << a.getLine(0) << std::endl; 
    std::cout << a.getLine(0);
    std::cout << a.getLine(1);
    // EXPECT_EQ(a.getLine(0),"a\n");
    // EXPECT_EQ(a.getLine(1),"y");
    return 0;
}