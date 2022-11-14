#include <gtest/gtest.h>

#include <project.hpp>

TEST(DefaultTest, Test) {
    EXPECT_EQ((2 * 2), 4);
}

TEST(Test1, test2) {
    EXPECT_EQ(3, ret_int(2));
}
