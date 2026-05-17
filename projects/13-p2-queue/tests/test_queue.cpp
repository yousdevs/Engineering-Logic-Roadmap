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

TEST(QueueTest, EnqueueIncreasesQueueSize) {

    Queue<int> q;

    q.enqueue(1);
    q.enqueue(2);

    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 2);
}