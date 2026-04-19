#include <gtest/gtest.h>

TEST(Sanity, BasicAssertion) {
    EXPECT_EQ(1 + 1, 2);
}
TEST(Sanity, Fails) {
    EXPECT_EQ(1, 2);
}