//  #include "include/TextEditor.hpp"
// #include "interfaces/Command.hpp"
// #include "src/Command.cpp"
// #include "include/TextEditor.hpp"
// #include "src/TextEditor.cpp"
//  #include "include/WorkWithData.hpp"
// #include "src/WorkWithData.cpp"

#include "TextEditor.hpp"
#include "Command.hpp"
// #include "Command.cpp"
#include "TextEditor.hpp"
// #include "TextEditor.cpp"
#include "WorkWithData.hpp"
// #include "WorkWithData.cpp"


#include <iostream>
#include <fstream>

void EXPECT_EQ(char a, char b) {
    if (a != b) {
        std::cout << a << '|' << b << std::endl;
    }
}

#include <iostream>
int main() {
WorkWithLines work;

    std::vector <std::string> insertCommands;

    insertCommands.push_back(work.insertElementInPosition(0, "k"));
    insertCommands.push_back(work.insertElementInPosition(0,"e"));
    insertCommands.push_back(work.insertElementInPosition(0,"l"));
    insertCommands.push_back(work.insertElementInPosition(3,"\n"));

    insertCommands.push_back(work.insertElementInPosition(4,"m"));
    insertCommands.push_back(work.insertElementInPosition(5,"u"));
    insertCommands.push_back(work.insertElementInPosition(6,"s"));
    insertCommands.push_back(work.insertElementInPosition(7,"\n"));

    insertCommands.push_back(work.insertElementInPosition(8,"\n"));

    insertCommands.push_back(work.insertElementInPosition(9,"x"));
    insertCommands.push_back(work.insertElementInPosition(10,"y"));
    insertCommands.push_back(work.insertElementInPosition(11,"z"));
    insertCommands.push_back(work.insertElementInPosition(12,"\n"));

    insertCommands.push_back(work.insertElementInPosition(13,"x"));
    
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
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(neededCommand[0]));
    for (size_t i = 0; i < neededResults1.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults1[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }


    // tmpCheck = workWithCommands.getStartOfLine(0);
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(neededCommand[1]));
    // for (size_t i = 0; i < neededResults2.size(); ++i) {
    //     if (tmpCheck->isVisible) {
    //         EXPECT_EQ(tmpCheck->_value, neededResults2[i][0]);
    //     } else {
    //         --i;
    //     }

    //     tmpCheck = tmpCheck->next;
    // }
    
    // tmpCheck = workWithCommands.getStartOfLine(0);
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(neededCommand[2]));
    // for (size_t i = 0; i < neededResults3.size(); ++i) {
    //     if (tmpCheck->isVisible) {
    //         EXPECT_EQ(tmpCheck->_value, neededResults3[i][0]);
    //     } else {
    //         --i;
    //     }

    //     tmpCheck = tmpCheck->next;
    // }

    // tmpCheck = workWithCommands.getStartOfLine(0);
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(neededCommand[3]));
    // for (size_t i = 0; i < neededResults4.size(); ++i) {
    //     if (tmpCheck->isVisible) {
    //         EXPECT_EQ(tmpCheck->_value, neededResults4[i][0]);
    //     } else {
    //         --i;
    //     }

    //     tmpCheck = tmpCheck->next;
    // }

    //  tmpCheck = workWithCommands.getStartOfLine(0);
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(neededCommand[4]));
    // for (size_t i = 0; i < neededResults5.size(); ++i) {
    //     if (tmpCheck->isVisible) {
    //         EXPECT_EQ(tmpCheck->_value, neededResults5[i][0]);
    //     } else {
    //         --i;
    //     }

    //     tmpCheck = tmpCheck->next;
    // }

    //  tmpCheck = workWithCommands.getStartOfLine(0);
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(neededCommand[5]));
    // for (size_t i = 0; i < neededResults6.size(); ++i) {
    //     if (tmpCheck->isVisible) {
    //         EXPECT_EQ(tmpCheck->_value, neededResults6[i][0]);
    //     } else {
    //         --i;
    //     }

    //     tmpCheck = tmpCheck->next;
    // }

    //  tmpCheck = workWithCommands.getStartOfLine(0);
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(neededCommand[6]));
    // for (size_t i = 0; i < neededResults7.size(); ++i) {
    //     if (tmpCheck->isVisible) {
    //         EXPECT_EQ(tmpCheck->_value, neededResults7[i][0]);
    //     } else {
    //         --i;
    //     }

    //     tmpCheck = tmpCheck->next;
    // }

    //  tmpCheck = workWithCommands.getStartOfLine(0);
    // commandsDelete.push_back(workWithCommands.deleteElementFromPosition(neededCommand[7]));
    // for (size_t i = 0; i < neededResults8.size(); ++i) {
    //     if (tmpCheck->isVisible) {
    //         EXPECT_EQ(tmpCheck->_value, neededResults8[i][0]);
    //     } else {
    //         --i;
    //     }

    //     tmpCheck = tmpCheck->next;
    // }
    return 0;
}