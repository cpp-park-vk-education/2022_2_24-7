#include <gtest/gtest.h>
#include <string>
#include "chat.cpp"
using namespace std;

TEST(ChatTests, test1) {
    Chat temp("dir/srs");
    string tempstr = temp.getChatDir();
    EXPECT_EQ(tempstr, "dir/srs");
}

TEST(ChatTests, test2) {
    Chat temp("dir/srs");
    
    EXPECT_EQ(temp.wrightMessage("hello"), true);
}

TEST(ChatTests, test3) {
    Chat temp("dir/srs");
    
    EXPECT_EQ(temp.getWholeChat(), "true");
}

TEST(UserTests, test1) {
    User temp(1, "user1");
    
    EXPECT_EQ(temp.id, 1);
    EXPECT_EQ(temp.name, "user1");
}

TEST(ProjectTests, test1) {
    Project temp(1);
    
    EXPECT_EQ(temp.getID(), 1);
}
