// #include "include/TextEditor.hpp"
#include "src/TextEditor.cpp"

int main() {
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

    work.deleteElementFromPosition(2,0);
    work.deleteElementFromPosition(3,0);
    work.deleteElementFromPosition(2,0);
    work.deleteElementFromPosition(2,1);
    work.deleteElementFromPosition(0,0);
    work.deleteElementFromPosition(0,1);
    work.deleteElementFromPosition(0,0);
    work.deleteElementFromPosition(0,0);
    //work.deleteElementFromPosition(0,0);
    // commandsInResult.push_back(work.insertElementInPosition(0, 0, "a"));
    // commandsInResult.push_back(work.insertElementInPosition(0,0,"b"));
    
    // commandsInResult.push_back(work.insertElementInPosition(0,2,"\n"));
    
    // commandsInResult.push_back(work.insertElementInPosition(1,0,"\n"));
    
    // commandsInResult.push_back(work.insertElementInPosition(2,0,"x"));
    // commandsInResult.push_back(work.insertElementInPosition(2,0,"y"));
    // commandsInResult.push_back(work.insertElementInPosition(2,1,"\n"));
    // // WorkWithLines work;
    // // work.insertElementInPosition(0, 0, "a");
    // // work.insertElementInPosition(0,0,"b");
    // // work.insertElementInPosition(0,2,"\n");
    // // work.insertElementInPosition(1,0,"\n");
    // // work.insertElementInPosition(2,0,"x");
    
    // // char a = work.getStartOfLine(0)->_value;
    // // work.deleteElementFromPosition(0,0);
    
    return 0;
}