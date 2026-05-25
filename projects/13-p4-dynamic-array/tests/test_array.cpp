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

TEST(AccessTest, OperatorBracketReadsCorrectly) {

    DynamicArray<int> arr = {10, 20, 30};

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(AccessTest, OperatorBracketWritesCorrectly) {

    DynamicArray<int> arr = {1, 2, 3};
    arr[1]                = 99;

    EXPECT_EQ(arr[1], 99);
}

TEST(AccessTest, AtThrowsOnOutOfRange) {

    DynamicArray<int> arr = {1, 2, 3};

    EXPECT_THROW(arr.at(3), std::out_of_range);
    EXPECT_THROW(arr.at(100), std::out_of_range);
}

TEST(AccessTest, AtReturnsCorrectElement) {

    DynamicArray<int> arr = {5, 6, 7};

    EXPECT_EQ(arr.at(0), 5);
    EXPECT_EQ(arr.at(2), 7);
}

TEST(AccessTest, FrontAndBackReturnCorrectElements) {

    DynamicArray<int> arr = {1, 2, 3};

    EXPECT_EQ(arr.front(), 1);
    EXPECT_EQ(arr.back(), 3);
}

TEST(AccessTest, DataReturnsRawPointer) {

    DynamicArray<int> arr = {1, 2, 3};

    int* raw = arr.data();
    EXPECT_EQ(raw[0], 1);
    EXPECT_EQ(raw[2], 3);
}

TEST(AccessTest, ConstOverloadsWork) {

    const DynamicArray<int> arr = {4, 5, 6};

    EXPECT_EQ(arr[0], 4);
    EXPECT_EQ(arr.at(1), 5);
    EXPECT_EQ(arr.front(), 4);
    EXPECT_EQ(arr.back(), 6);
    EXPECT_EQ(arr.data()[2], 6);
}