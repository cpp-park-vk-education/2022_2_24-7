#include <gtest/gtest.h>
#include <iostream>

#include "WorkWithData.hpp"

TEST(interface, insert1) {
    WorkWithData a;
    a.userFirst(0,0);

    a.operationWithData("i:0|0|B:0", 1);
    a.operationWithData("i:1|1|A:0", 1);
    a.operationWithData("i:1|1|C:0", 1);
};

TEST(interface, delete1) {
    WorkWithData a;
    a.userFirst(0,0);

    a.operationWithData("i:0|0|B:0", 1);
    a.operationWithData("i:1|1|\n:0", 1);
    a.operationWithData("i:1|2|C:0", 1);
    a.operationWithData("i:1|3|C:0", 1);


    a.operationWithData("d:0");
    EXPECT_EQ(a.getLine(1), "\n");
    EXPECT_EQ(a.getLine(2), "CC");
};