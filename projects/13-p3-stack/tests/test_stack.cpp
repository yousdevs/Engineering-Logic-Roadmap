#include "Stack.hpp"

#include <gtest/gtest.h>

TEST(StackTest, TopOnEmptyThrows) {

    Stack<int> s;

    EXPECT_THROW(s.top(), std::runtime_error);
}