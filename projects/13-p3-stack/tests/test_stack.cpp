#include "Stack.hpp"

#include <gtest/gtest.h>

TEST(StackTest, DefaultConstructorIsEmpty) {

    Stack<int> s;

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, TopOnEmptyThrows) {

    Stack<int> s;

    EXPECT_THROW(s.top(), std::runtime_error);
}

TEST(StackTest, PushIncreasesSize) {

    Stack<int> s;

    s.push(10);
    s.push(20);

    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 2);
}

TEST(StackTest, PushPopMaintainsLifoOrder) {

    Stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_EQ(s.top(), 3);

    s.pop();
    EXPECT_EQ(s.top(), 2);

    s.pop();
    EXPECT_EQ(s.top(), 1);
}

TEST(StackTest, PopOnEmptyThrows) {

    Stack<int> s;

    EXPECT_THROW(s.pop(), std::runtime_error);
}

TEST(StackTest, CopyConstructorCreatesIndependentCopy) {

    Stack<int> s1;

    s1.push(10);
    s1.push(20);

    Stack<int> s2(s1);

    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.top(), 20);

    s2.pop();
    EXPECT_EQ(s2.top(), 10);

    EXPECT_EQ(s1.size(), 2);
    EXPECT_EQ(s1.top(), 20);
}

TEST(StackTest, MoveConstructorTransfersState) {

    Stack<int> s1;

    s1.push(5);
    s1.push(6);

    Stack<int> s2(std::move(s1));

    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.top(), 6);

    s2.pop();
    EXPECT_EQ(s2.top(), 5);
}

TEST(StackTest, CopyAssignmentCreatesIndependentCopy) {

    Stack<int> s1;
    s1.push(1);
    s1.push(2);

    Stack<int> s2;
    s2 = s1;

    EXPECT_EQ(s2.top(), 2);

    s2.pop();
    EXPECT_EQ(s2.top(), 1);

    EXPECT_EQ(s1.top(), 2);
}

TEST(StackTest, MoveAssignmentTransfersState) {

    Stack<int> s1;
    s1.push(100);
    s1.push(200);

    Stack<int> s2;
    s2 = std::move(s1);

    EXPECT_EQ(s2.top(), 200);

    s2.pop();
    EXPECT_EQ(s2.top(), 100);
}

TEST(StackTest, SelfAssignmentDoesNotCorruptState) {

    Stack<int> s;

    s.push(7);
    s.push(8);

    s = s;

    EXPECT_EQ(s.top(), 8);
    EXPECT_EQ(s.size(), 2);
}

TEST(StackTest, SwapExchangesFullState) {

    Stack<int> a;
    Stack<int> b;

    a.push(1);
    a.push(2);
    a.push(3);

    b.push(10);
    b.push(20);

    a.swap(b);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 3);

    EXPECT_EQ(a.top(), 20);
    a.pop();
    EXPECT_EQ(a.top(), 10);

    EXPECT_EQ(b.top(), 3);
    b.pop();
    EXPECT_EQ(b.top(), 2);
    b.pop();
    EXPECT_EQ(b.top(), 1);
}

TEST(StackTest, ConstructFromContainerCopiesElements) {

    DoublyLinkedList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Stack<int> s(list);

    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.top(), 3);

    s.pop();
    EXPECT_EQ(s.top(), 2);

    s.pop();
    EXPECT_EQ(s.top(), 1);

    // original container must remain unchanged
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 3);
}

TEST(StackTest, ConstructFromContainerMovesElements) {

    DoublyLinkedList<int> list;

    list.push_back(10);
    list.push_back(20);

    Stack<int> s(std::move(list));

    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.top(), 20);

    s.pop();
    EXPECT_EQ(s.top(), 10);
}