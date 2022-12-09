// #include "include/TextEditor.hpp"
#include "src/TextEditor.cpp"

int main() {
    WorkWithLines work;
    work.insertElementInPosition(0, 0, "a");
    work.insertElementInPosition(0,0,"b");
    work.insertElementInPosition(0,2,"\n");
    work.insertElementInPosition(1,0,"\n");
    work.insertElementInPosition(2,0,"x");

    
    return 0;
}