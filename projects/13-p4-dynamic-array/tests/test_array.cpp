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