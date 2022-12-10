#include <gtest/gtest.h>
#include <iostream>

#include "TextEditor.hpp"

TEST(TextEditor, insertElemnetsNotCommand) {
    std::vector<std::string> commandsInResult;
    
    WorkWithLines work;
    commandsInResult.push_back(work.insertElementInPosition(0, 0, "a"));
    commandsInResult.push_back(work.insertElementInPosition(0,0,"b"));
    
    commandsInResult.push_back(work.insertElementInPosition(0,2,"\n"));
    
    commandsInResult.push_back(work.insertElementInPosition(1,0,"\n"));
    
    commandsInResult.push_back(work.insertElementInPosition(2,0,"x"));
    commandsInResult.push_back(work.insertElementInPosition(2,0,"y"));
    commandsInResult.push_back(work.insertElementInPosition(2,1,"\n"));
    
    // transfer line!!! TODO

    std::vector<std::string> neededCommand = {"i:1|0|a:0", "i:2|0|b:1|0:2", "i:3|0|\n:1|0:1",
         "i:4|0|\n:3|0:1", "i:5|0|x:4|0:1", "i:6|0|y:4|0:5|0:3", "i:7|0|\n:6|0:5|0:3"};
    std::vector<std::string> neededResults = {"b", "a", "\n", "\n", "y", "\n", "x"};

    Element* tmpCheck = work.getStartOfLine(0);
    
    for (size_t i = 0; i < neededResults.size(); ++i) {
        EXPECT_EQ(tmpCheck->_value, neededResults[i][0]);
        EXPECT_EQ(commandsInResult[i], neededCommand[i]);
        
        tmpCheck = tmpCheck->next;
    }
}

TEST(TextEditor, deleteElementsNotCommand) {
    std::vector<std::string> commandsInResult;
    
    WorkWithLines work;
    // lek\n
    // mus\n
    // \n
    // xyz\n
    // x

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

    work.insertElementInPosition(4,0,"\n");
    
    std::vector<std::string> neededCommand = {"i:1|0|a:0", "i:2|0|b:1|0:2", "i:3|0|\n:1|0:1",
         "i:4|0|\n:3|0:1", "i:5|0|x:4|0:1", "", "", "", ""};

    // first
    std::vector<std::string> neededResults = {"l", "e", "k", "\n", "m", "u", "s", "\n", "\n", "x", "y", "z", "\n", "x"};
    // delete 2
    std::vector<std::string> neededResults1 = {"l", "e", "k", "\n", "m", "u", "s", "\n", "x", "y", "z", "\n", "x"};
    // delete 4
    std::vector<std::string> neededResults2 = {"l", "e", "k", "\n", "m", "u", "s", "\n", "x", "y", "z", "\n"};
    // delete x from 3
    std::vector<std::string> neededResults3 = {"l", "e", "k", "\n", "m", "u", "s", "\n", "x", "y", "z", "\n"};
    // delete z from 3
    std::vector<std::string> neededResults4 = {"l", "e", "k", "\n", "m", "u", "s", "\n", "x", "y", "\n"};
    // delete l
    std::vector<std::string> neededResults5 = {"e", "k", "\n", "m", "u", "s", "\n", "x", "y", "\n"};
    // delete k
    std::vector<std::string> neededResults6 = {"e", "\n", "m", "u", "s", "\n", "x", "y", "\n"};
    // delete e
    std::vector<std::string> neededResults7 = {"\n", "m", "u", "s", "\n", "x", "y", "\n"};
    // delete \n
    std::vector<std::string> neededResults8 = {"m", "u", "s", "\n", "x", "y", "\n"};


    Element* tmpCheck = work.getStartOfLine(0);
    
    for (size_t i = 0; i < neededResults.size(); ++i) {
        EXPECT_EQ(tmpCheck->_value, neededResults[i][0]);

        tmpCheck = tmpCheck->next;
    }

    work.deleteElementFromPosition(2,0);
    for (size_t i = 0; i < neededResults1.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults1[i][0]);
        }

        tmpCheck = tmpCheck->next;
    }

    work.deleteElementFromPosition(3,0);
    for (size_t i = 0; i < neededResults2.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults2[i][0]);
        }

        tmpCheck = tmpCheck->next;
    }

    work.deleteElementFromPosition(2,0);
    for (size_t i = 0; i < neededResults3.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults3[i][0]);
        }

        tmpCheck = tmpCheck->next;
    }

    work.deleteElementFromPosition(2,1);
    for (size_t i = 0; i < neededResults3.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults3[i][0]);
        }

        tmpCheck = tmpCheck->next;
    }

    work.deleteElementFromPosition(0,0);
    for (size_t i = 0; i < neededResults3.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults3[i][0]);
        }

        tmpCheck = tmpCheck->next;
    }

    work.deleteElementFromPosition(0,0);
    for (size_t i = 0; i < neededResults3.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults3[i][0]);
        }

        tmpCheck = tmpCheck->next;
    }

    work.deleteElementFromPosition(0,0);
    for (size_t i = 0; i < neededResults3.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults3[i][0]);
        }

        tmpCheck = tmpCheck->next;
    }
}
