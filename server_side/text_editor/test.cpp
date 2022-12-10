// #include "include/TextEditor.hpp"
#include "src/TextEditor.cpp"

int main() {
    std::vector<std::string> commandsInResult;
    
    WorkWithLines work;
    commandsInResult.push_back(work.insertElementInPosition(0, 0, "a"));
    commandsInResult.push_back(work.insertElementInPosition(0,0,"b"));
    
    commandsInResult.push_back(work.insertElementInPosition(0,2,"\n"));
    
    commandsInResult.push_back(work.insertElementInPosition(1,0,"\n"));
    
    commandsInResult.push_back(work.insertElementInPosition(2,0,"x"));
    commandsInResult.push_back(work.insertElementInPosition(2,0,"y"));
    commandsInResult.push_back(work.insertElementInPosition(2,1,"\n"));
    // WorkWithLines work;
    // work.insertElementInPosition(0, 0, "a");
    // work.insertElementInPosition(0,0,"b");
    // work.insertElementInPosition(0,2,"\n");
    // work.insertElementInPosition(1,0,"\n");
    // work.insertElementInPosition(2,0,"x");
    
    // char a = work.getStartOfLine(0)->_value;
    // work.deleteElementFromPosition(0,0);
    
    return 0;
}