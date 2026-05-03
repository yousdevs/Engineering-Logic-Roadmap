#include "doubly_linked_list.hpp"

#include <gtest/gtest.h>

TEST(DoublyLinkedListTest, DefaultConstructorIsEmpty) {

    DoublyLinkedList<int> list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

TEST(DoublyLinkedListTest, MoveConstructorLeavesSourceEmpty) {

    // TODO: after push_back
}

TEST(IteratorTest, BeginEqualsEndOnEmptyList) {

    DoublyLinkedList<int> list;
    EXPECT_EQ(list.begin(), list.end());
}

TEST(ModifiersTest, PushBackIncreasesSize) {

    DoublyLinkedList<int> list;

    list.push_back(1);
    list.push_back(2);

    EXPECT_EQ(list.size(), 2);
}

TEST(ModifiersTest, PushFrontPushesToFront) {

    DoublyLinkedList<int> list;

    list.push_back(2);
    list.push_front(1);

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

TEST(ModifiersTest, PopBackDecreasesSize) {

    DoublyLinkedList<int> list;

    list.push_back(1);
    EXPECT_EQ(list.size(), 1);

    list.pop_back();
    EXPECT_EQ(list.size(), 0);
}

TEST(ModifiersTest, PopFrontOnSingleElementLeavesListEmpty) {

    DoublyLinkedList<int> list;

    list.push_front(1);
    list.pop_front();

    EXPECT_EQ(list.size(), 0);
}

TEST(ModifiersTest, IterationMatchesInsertionOrder) {

    DoublyLinkedList<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::vector<int> result;

    for (auto it = list.begin(); it != list.end(); ++it)
        result.push_back(*it);

    EXPECT_EQ(result, (std::vector<int>{1, 2, 3}));
}

TEST(ConstIteratorTest, CanIterateOverConstList) {

    const DoublyLinkedList<int> list = {1, 2, 3};

    int sum = 0;
    for (const auto& v : list)
        sum += v;

    EXPECT_EQ(sum, 6);
}

TEST(ConstIteratorTest, InitializerListConstructsCorrectly) {

    DoublyLinkedList<int> list = {10, 20, 30};

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
    EXPECT_EQ(list.size(), 3);
}