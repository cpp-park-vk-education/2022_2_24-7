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

    for (size_t i = 0; i < commandsInResult.size(); ++i) {
        EXPECT_EQ(commandsInResult[i], neededCommand[i]);
    }

}

TEST(TextEditor, insertCommand) {
    std::vector<std::string> commandsInResult;
    
    WorkWithLines work;

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

    WorkWithLines workCommand;
    for (auto i: commandsInResult) {
        workCommand.insertElementInPosition(i);
    }

    Element* tmpForTransfer = work.getStartOfLine(1);
    Element* tmpForTransfer1 = workCommand.getStartOfLine(1);

    while (tmpForTransfer && tmpForTransfer1) {
        EXPECT_EQ(tmpForTransfer1->_value, tmpForTransfer->_value);
        
        tmpForTransfer1 = tmpForTransfer1->next;
        tmpForTransfer = tmpForTransfer->next;
    }

}

TEST(TextEditor, deleteCommand) {
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
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(2,0));
    for (size_t i = 0; i < neededResults1.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults1[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    tmpCheck = workWithCommands.getStartOfLine(0);
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(3,0));
    for (size_t i = 0; i < neededResults2.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults2[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    tmpCheck = workWithCommands.getStartOfLine(0);
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(2,0));
    for (size_t i = 0; i < neededResults3.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults3[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

    tmpCheck = workWithCommands.getStartOfLine(0);
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(2,1));
    for (size_t i = 0; i < neededResults4.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults4[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

     tmpCheck = workWithCommands.getStartOfLine(0);
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    for (size_t i = 0; i < neededResults5.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults5[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

     tmpCheck = workWithCommands.getStartOfLine(0);
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,1));
    for (size_t i = 0; i < neededResults6.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults6[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

     tmpCheck = workWithCommands.getStartOfLine(0);
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    for (size_t i = 0; i < neededResults7.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults7[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }

     tmpCheck = workWithCommands.getStartOfLine(0);
    commandsDelete.push_back(workWithCommands.deleteElementFromPosition(0,0));
    for (size_t i = 0; i < neededResults8.size(); ++i) {
        if (tmpCheck->isVisible) {
            EXPECT_EQ(tmpCheck->_value, neededResults8[i][0]);
        } else {
            --i;
        }

        tmpCheck = tmpCheck->next;
    }
}