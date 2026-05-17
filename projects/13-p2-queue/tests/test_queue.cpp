#include "Queue.hpp"

#include <gtest/gtest.h>

TEST(QueueTest, DefaultConstructorIsEmpty) {

    Queue<int> q;

    EXPECT_EQ(q.size(), 0);
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, FrontAccessOnEmptyQueueThrows) {

    Queue<int> q;

    EXPECT_THROW(q.front(), std::runtime_error);
}