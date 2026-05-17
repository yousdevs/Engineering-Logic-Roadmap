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

TEST(QueueTest, DequeueDecreasesQueueSize) {

    Queue<int> q;

    q.enqueue(1);
    q.enqueue(2);

    EXPECT_EQ(q.front(), 1);

    q.dequeue();
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 2);
}

TEST(QueueTest, DequeueEmptyQueueThrows) {

    Queue<int> q;

    EXPECT_THROW(q.dequeue(), std::runtime_error);
}

TEST(QueueTest, SwapExchangesEntireQueueState) {

    Queue<int> q1;
    Queue<int> q2;

    q1.enqueue(1);
    q1.enqueue(2);
    q1.enqueue(3);

    q2.enqueue(10);
    q2.enqueue(20);

    q1.swap(q2);

    EXPECT_EQ(q1.size(), 2);
    EXPECT_EQ(q1.front(), 10);

    q1.dequeue();
    EXPECT_EQ(q1.front(), 20);

    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), 1);

    q2.dequeue();
    EXPECT_EQ(q2.front(), 2);

    q2.dequeue();
    EXPECT_EQ(q2.front(), 3);
}