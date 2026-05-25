#include "array.hpp"

#include <gtest/gtest.h>

TEST(ConstructionTest, DefaultConstructorIsEmpty) {

    DynamicArray<int> arr;

    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.capacity(), 0);
}

TEST(ConstructionTest, CountConstructorDefaultConstructElements) {

    DynamicArray<int> arr(5);

    EXPECT_EQ(arr.size(), 5);
    EXPECT_FALSE(arr.empty());
    EXPECT_EQ(arr.capacity(), 5);
}

TEST(ConstructionTest, FillConstuctorFillsWithValue) {

    DynamicArray<int> arr(4, 2);

    EXPECT_EQ(arr.size(), 4);

    // TODO accessor
}

TEST(ConstructionTest, InitializerListConstructsCorrectly) {

    DynamicArray<int> arr = {1, 2, 3};
    EXPECT_EQ(arr.size(), 3);
}

TEST(ConstructionTest, DestuctorRunsWithoutLeak) {

    {
        DynamicArray<int> arr(10, 7);
    }
}

TEST(CopyMoveTest, CopyConstructorIsDeepCopy) {

    DynamicArray<int> arr = {1, 2, 3};
    DynamicArray<int> copy(arr);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(arr.size(), 3);
}

TEST(CopyMoveTest, MoveConstructorLeavesSourceEmpty) {

    DynamicArray<int> arr = {1, 2, 3};
    DynamicArray<int> moved(std::move(arr));

    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 0);
}

TEST(CopyMoveTest, CopyAssignmentIsDeepCopy) {

    DynamicArray<int> a = {1, 2};
    DynamicArray<int> b = {9, 8, 7};
    b                   = a;

    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(a.size(), 2);
}

TEST(CopyMoveTest, MoveAssignmentTransfersOwnership) {

    DynamicArray<int> a = {1, 2, 3};
    DynamicArray<int> b;
    b = std::move(a);

    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(a.size(), 0);
}

TEST(CopyMoveTest, SelfAssignmentIsHarmless) {

    DynamicArray<int> arr = {1, 2, 3};
    arr                   = arr;

    EXPECT_EQ(arr.size(), 3);
}

TEST(CopyMoveTest, InitializerListAssignment) {

    DynamicArray<int> arr = {1, 2};
    arr                   = {10, 20, 30};

    EXPECT_EQ(arr.size(), 3);
}