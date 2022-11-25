#include <gtest/gtest.h>

#include "client.hpp"

TEST(DefaultTest, client1) { EXPECT_EQ((2 * 2), 4); }

TEST(DefaultTest, client2) { EXPECT_EQ((2 * 2), 7); }
