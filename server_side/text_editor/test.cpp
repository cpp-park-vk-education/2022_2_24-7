 #include "include/TextEditor.hpp"
#include "include/Command.hpp"
#include "src/Command.cpp"
#include "include/TextEditor.hpp"
#include "src/TextEditor.cpp"
 #include "include/WorkWithData.hpp"
// #include "src/WorkWithData.cpp"

void EXPECT_EQ(char a, char b) {
    if (a != b) {
        std::cout << a << '|' << b << std::endl;
    }
}

#include <iostream>
int main() {
   WorkWithLines work;

    work.insertElementInPosition(0, "k");
    work.insertElementInPosition(0,"e");
    work.insertElementInPosition(0,"l");
    work.insertElementInPosition(3,"\n");

    work.insertElementInPosition(4,"m");
    work.insertElementInPosition(5,"u");
    work.insertElementInPosition(6,"s");
    work.insertElementInPosition(7,"\n");

    work.insertElementInPosition(8,"\n");

    work.insertElementInPosition(9,"x");
    work.insertElementInPosition(10,"y");
    work.insertElementInPosition(11,"z");
    work.insertElementInPosition(12,"\n");

    work.insertElementInPosition(13,"x");
    
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

    

    std::vector<std::string> commandsInResult;
    Element* tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults.size(); ++i) {
        EXPECT_EQ(tmpCheck->_value, neededResults[i][0]);

        tmpCheck = tmpCheck->next;
    }

    commandsInResult.push_back(work.deleteElementFromPosition(2,0));
    tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults1.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults1[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    commandsInResult.push_back(work.deleteElementFromPosition(3,0));
    tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults2.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults2[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    commandsInResult.push_back(work.deleteElementFromPosition(2,0));
    tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults3.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults3[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    commandsInResult.push_back(work.deleteElementFromPosition(2,1));
    tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults4.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults4[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    commandsInResult.push_back(work.deleteElementFromPosition(0,0));
    tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults5.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults5[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    commandsInResult.push_back(work.deleteElementFromPosition(0,1));
    tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults6.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults6[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    commandsInResult.push_back(work.deleteElementFromPosition(0,0));
    tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults7.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults7[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    commandsInResult.push_back(work.deleteElementFromPosition(0,0));
    tmpCheck = work.getStartOfLine(0);
    for (size_t i = 0; i < neededResults8.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults8[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    tmpCheck = work.getStartOfLine(0);
    work.insertElementInPosition(0,"W");
    work.insertElementInPosition(7,"X");
    tmpCheck = work.getStartOfLine(0);

    return 0;
}