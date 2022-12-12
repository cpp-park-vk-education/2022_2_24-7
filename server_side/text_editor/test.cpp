// #include "include/TextEditor.hpp"
#include "include/Command.hpp"
#include "src/Command.cpp"
#include "include/TextEditor.hpp"
#include "src/TextEditor.cpp"

int main() {
    std::vector<std::string> commandsInResult;
    
    WorkWithLines work;
    /*
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
    */
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
    return 0;
}