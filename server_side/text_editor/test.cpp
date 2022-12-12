// #include "include/TextEditor.hpp"
#include "include/Command.hpp"
#include "src/Command.cpp"
#include "include/TextEditor.hpp"
#include "src/TextEditor.cpp"
#include "include/WorkWithData.hpp"
#include "src/WorkWithData.cpp"

#include <iostream>
int main() {
    /*
    std::vector<std::string> commandsInResult;
    
    WorkWithLines work;
    
    work.insertElementInPosition(0, 0, "k");
    work.insertElementInPosition(0,0,"e");
    work.insertElementInPosition(0,0,"l");
    work.insertElementInPosition(0,3,"\n");

    work.insertElementInPosition(1,0,"m");
    work.insertElementInPosition(1,1,"u");
    work.insertElementInPosition(1,2,"s");
    work.insertElementInPosition(1,3,"\n");

    work.insertElementInPosition(2,0,"\n");

    work.insertElementInPosition(3,0,"x");
    work.insertElementInPosition(3,1,"y");
    work.insertElementInPosition(3,2,"z");
    work.insertElementInPosition(3,3,"\n");

    work.insertElementInPosition(4,0,"x");
    work.insertElementInPosition(4,1,"\n");

    work.insertElementInPosition(5,0,"\n");
    
    // work.deleteElementFromPosition(4,1);
    // work.deleteElementFromPosition(4,1);
    // work.insertElementInPosition(4,0,"\n");

    commandsInResult.push_back(work.insertElementInPosition(0, 0, "k"));
    commandsInResult.push_back(work.insertElementInPosition(0,0,"e"));
    commandsInResult.push_back(work.insertElementInPosition(0,0,"l"));
    commandsInResult.push_back(work.insertElementInPosition(0,3,"\n"));

    commandsInResult.push_back(work.insertElementInPosition(1,0,"m"));
    commandsInResult.push_back(work.insertElementInPosition(1,1,"u"));
    commandsInResult.push_back(work.insertElementInPosition(1,2,"s"));
    commandsInResult.push_back(work.insertElementInPosition(1,3,"\n"));

    commandsInResult.push_back(work.insertElementInPosition(2,0,"\n"));

    commandsInResult.push_back(work.insertElementInPosition(3,0,"x"));
    commandsInResult.push_back(work.insertElementInPosition(3,1,"y"));
    commandsInResult.push_back(work.insertElementInPosition(3,2,"z"));
    commandsInResult.push_back(work.insertElementInPosition(3,3,"\n"));

    commandsInResult.push_back(work.insertElementInPosition(4,0,"x"));
    commandsInResult.push_back(work.insertElementInPosition(4,1,"\n"));

    commandsInResult.push_back(work.insertElementInPosition(5,0,"\n"));

    WorkWithLines work1;
    for(auto i: commandsInResult) {
        work1.insertElementInPosition(i);
    }
    
    work1.deleteElementFromPosition("d:1|0");
    */

    
    WorkWithLines work;

    std::vector <std::string> insertCommands;

    insertCommands.push_back(work.insertElementInPosition(0, 0, "k"));
    insertCommands.push_back(work.insertElementInPosition(0,0,"e"));
    insertCommands.push_back(work.insertElementInPosition(0,0,"l"));
    insertCommands.push_back(work.insertElementInPosition(0,3,"\n"));

    insertCommands.push_back(work.insertElementInPosition(1,0,"m"));
    insertCommands.push_back(work.insertElementInPosition(1,1,"u"));
    insertCommands.push_back(work.insertElementInPosition(1,2,"s"));
    insertCommands.push_back(work.insertElementInPosition(1,3,"\n"));

    insertCommands.push_back(work.insertElementInPosition(2,0,"\n"));

    insertCommands.push_back(work.insertElementInPosition(3,0,"x"));
    insertCommands.push_back(work.insertElementInPosition(3,1,"y"));
    insertCommands.push_back(work.insertElementInPosition(3,2,"z"));
    insertCommands.push_back(work.insertElementInPosition(3,3,"\n"));

    insertCommands.push_back(work.insertElementInPosition(4,0,"x"));
    
    WorkWithLines workWithCommands;

    for (auto i : insertCommands) {
        workWithCommands.insertElementInPosition(i);
    }
    
    std::vector<std::string> commandsDelete;
    
    std::vector<std::string> neededCommand = {"d:9|0|", "d:14|0|", "d:10|0|",
         "d:12|0|", "d:3|0|", "d:1|0|", "d:2|0|", "d:4|0|"};

    // first
    std::vector<std::string> neededResults = {"l", "e", "k", "\n", "m", "u", "s", "\n", "\n", "x", "y", "z", "\n", "x"};
    // delete 2
    std::vector<std::string> neededResults1 = {"l", "e", "k", "\n", "m", "u", "s", "\n", "x", "y", "z", "\n", "x"};
    // delete 4
    std::vector<std::string> neededResults2 = {"l", "e", "k", "\n", "m", "u", "s", "\n", "x", "y", "z", "\n"};
    // delete x from 3
    std::vector<std::string> neededResults3 = {"l", "e", "k", "\n", "m", "u", "s", "\n", "y", "z", "\n"};
    // delete z from 3
    std::vector<std::string> neededResults4 = {"l", "e", "k", "\n", "m", "u", "s", "\n", "y", "\n"};
    // delete l
    std::vector<std::string> neededResults5 = {"e", "k", "\n", "m", "u", "s", "\n", "y", "\n"};
    // delete k
    std::vector<std::string> neededResults6 = {"e", "\n", "m", "u", "s", "\n", "y", "\n"};
    // delete e
    std::vector<std::string> neededResults7 = {"\n", "m", "u", "s", "\n", "y", "\n"};
    // delete \n
    std::vector<std::string> neededResults8 = {"m", "u", "s", "\n", "y", "\n"};

    Element* tmpCheck = workWithCommands.getStartOfLine(0);
    for (size_t i = 0; i < 14; ++i) {
        commandsDelete.push_back(workWithCommands.deleteElementFromPosition(insertCommands[i]));
    }
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(3,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(2,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(2,1));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,1));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));

    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));

    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));

    if (nullptr == workWithCommands.getStartOfLine(0)) {
        std::cout << "XA" << std::endl;
    };

    WorkWithData a1;
    a1.userFirst(0,0);

    a1.operationWithData("i:a:0");
    a1.operationWithData("i:h:0");
    a1.operationWithData("d:1");


    WorkWithData a;
    a.userFirst(0,0);
    for (auto i : insertCommands) {
        a.operationWithData(i, 1);
    }

    for (auto i : commandsDelete) {
        a.operationWithData(i, 1);
    }
    
    return 0;
}