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
