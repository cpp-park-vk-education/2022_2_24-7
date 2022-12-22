#include <gtest/gtest.h>
#include <iostream>

#include "WorkWithData.hpp"

TEST(interface, insert1) {
    WorkWithData a;
    a.userFirst(0,0);

    a.operationWithData("i:0|0:0", 1);

    // std::cout << "1" <<std::endl;
    // a.operationWithData("i:a:0");
    // std::cout << "1.1" <<std::endl;
    // a.operationWithData("i:b:1");
    // std::cout << "1.2" <<std::endl;
    // a.operationWithData("i:\n:1");
    // std::cout << "2" <<std::endl;
    // EXPECT_EQ(a.getLine(1), "a\n");
    // EXPECT_EQ(a.getLine(2), "b");
    // std::cout << "3" <<std::endl;
};

TEST(interface, delete1) {
    WorkWithData a;
    a.userFirst(0,0);

    a.operationWithData("i:a:0");
    a.operationWithData("i:b:1");
    a.operationWithData("i:\n:1");

    a.operationWithData("d:0");
    EXPECT_EQ(a.getLine(1), "\n");
    EXPECT_EQ(a.getLine(2), "b");

};