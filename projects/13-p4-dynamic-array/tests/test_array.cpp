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

TEST(IteratorTest, BeginEqualsEndOnEmptyArray) {

    DynamicArray<int> arr;

    EXPECT_EQ(arr.begin(), arr.end());
}

TEST(IteratorTest, ForwardIterationMatchesOrder) {

    DynamicArray<int> arr = {1, 2, 3};
    std::vector<int>  result;

    for (auto it = arr.begin(); it != arr.end(); ++it)
        result.push_back(*it);

    EXPECT_EQ(result, (std::vector<int>{1, 2, 3}));
}

TEST(IteratorTest, RangeBasedForLoop) {

    DynamicArray<int> arr = {4, 5, 6};
    int               sum = 0;

    for (auto& v : arr)
        sum += v;

    EXPECT_EQ(sum, 15);
}

TEST(IteratorTest, RandomAccessArithmetic) {

    DynamicArray<int> arr = {10, 20, 30};
    auto              it  = arr.begin();

    EXPECT_EQ(*(it + 2), 30);
    EXPECT_EQ(it[1], 20);
}

TEST(IteratorTest, IteratorSubtractionGivesDistance) {

    DynamicArray<int> arr = {1, 2, 3, 4};

    EXPECT_EQ(arr.end() - arr.begin(), 4);
}

TEST(IteratorTest, IteratorComparisonOperators) {

    DynamicArray<int> arr = {1, 2, 3};

    EXPECT_LT(arr.begin(), arr.end());
    EXPECT_GT(arr.end(), arr.begin());
    EXPECT_LE(arr.begin(), arr.begin());
}

TEST(ConstIteratorTest, CanIterateConstArray) {

    const DynamicArray<int> arr = {1, 2, 3};
    int                     sum = 0;
    for (const auto& v : arr)
        sum += v;

    EXPECT_EQ(sum, 6);
}

TEST(ConstIteratorTest, CbeginCendWork) {

    DynamicArray<int> arr = {7, 8, 9};
    auto              it  = arr.cbegin();

    EXPECT_EQ(*it, 7);
    EXPECT_EQ(arr.cend() - arr.cbegin(), 3);
}

TEST(ConstIteratorTest, ImplicitConversionFromIterator) {

    DynamicArray<int>                 arr = {1, 2, 3};
    DynamicArray<int>::const_iterator it  = arr.begin();

    EXPECT_EQ(*it, 1);
}

TEST(PushPopTest, PushBackIncreasesSize) {

    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(PushPopTest, PushBackTriggersReallocationTransparently) {

    DynamicArray<int> arr;
    for (int i = 0; i < 100; ++i)
        arr.push_back(i);

    EXPECT_EQ(arr.size(), 100);

    for (int i = 0; i < 100; ++i)
        EXPECT_EQ(arr[i], i);
}

TEST(PushPopTest, PopBackDecreasesSize) {

    DynamicArray<int> arr = {1, 2, 3};
    arr.pop_back();

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.back(), 2);
}

TEST(PushPopTest, MoveSemanticsPushBack) {

    DynamicArray<std::string> arr;
    std::string               s = "hello";
    arr.push_back(std::move(s));

    EXPECT_EQ(arr[0], "hello");
    EXPECT_TRUE(s.empty());
}

TEST(PushPopTest, EmplaceBackConstructsInPlace) {

    struct Point {
            int x, y;
            Point(int x_, int y_) : x(x_), y(y_) {}
    };

    DynamicArray<Point> arr;
    arr.emplace_back(1, 2);

    EXPECT_EQ(arr.back().x, 1);
    EXPECT_EQ(arr.back().y, 2);
}

TEST(PushPopTest, CapacityGrowsOnDemand) {

    DynamicArray<int> arr;

    EXPECT_EQ(arr.capacity(), 0);

    arr.push_back(1);

    EXPECT_GE(arr.capacity(), 1);

    std::size_t cap = arr.capacity();
    // push until reallocation
    while (arr.size() < cap)
        arr.push_back(0);

    arr.push_back(0);  // triggers growth

    EXPECT_GT(arr.capacity(), cap);
}

TEST(CapacityTest, ReserveIncreasesCapacityWithoutChangingSize) {

    DynamicArray<int> arr;
    arr.reserve(100);

    EXPECT_GE(arr.capacity(), 100);
    EXPECT_EQ(arr.size(), 0);
}

TEST(CapacityTest, ReserveDoesNothingIfAlreadySufficient) {

    DynamicArray<int> arr;
    arr.reserve(10);
    std::size_t cap = arr.capacity();
    arr.reserve(5);

    EXPECT_EQ(arr.capacity(), cap);
}

TEST(CapacityTest, ShrinkToFitReleasesExcessCapacity) {

    DynamicArray<int> arr;
    arr.reserve(100);
    arr.push_back(1);
    arr.push_back(2);
    arr.shrink_to_fit();

    EXPECT_EQ(arr.capacity(), arr.size());
    EXPECT_EQ(arr.size(), 2);
}

TEST(CapacityTest, ResizeGrowsWithDefaultValues) {

    DynamicArray<int> arr = {1, 2, 3};
    arr.resize(6);

    EXPECT_EQ(arr.size(), 6);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[4], 0);
}

TEST(CapacityTest, ResizeShrinks) {

    DynamicArray<int> arr = {1, 2, 3, 4, 5};
    arr.resize(2);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.back(), 2);
}

TEST(CapacityTest, ResizeWithValueFillsNewElements) {

    DynamicArray<int> arr = {1, 2};
    arr.resize(5, 42);

    EXPECT_EQ(arr[2], 42);
    EXPECT_EQ(arr[4], 42);
}

TEST(InsertEraseTest, InsertAtBeginShiftsElements) {

    DynamicArray<int> arr = {2, 3, 4};
    arr.insert(arr.cbegin(), 1);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr.size(), 4);
}

TEST(InsertEraseTest, InsertInMiddle) {

    DynamicArray<int> arr = {1, 3};
    arr.insert(arr.cbegin() + 1, 2);

    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr.size(), 3);
}

TEST(InsertEraseTest, InsertReturnsIteratorToInsertedElement) {

    DynamicArray<int> arr = {1, 3};
    auto              it  = arr.insert(arr.cbegin() + 1, 2);

    EXPECT_EQ(*it, 2);
}

TEST(InsertEraseTest, EraseMiddleElement) {

    DynamicArray<int> arr = {1, 2, 3};
    arr.erase(arr.cbegin() + 1);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(InsertEraseTest, EraseRange) {

    DynamicArray<int> arr = {1, 2, 3, 4, 5};
    arr.erase(arr.cbegin() + 1, arr.cbegin() + 4);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 5);
}

TEST(InsertEraseTest, EraseReturnsIteratorToNextElement) {

    DynamicArray<int> arr = {1, 2, 3};
    auto              it  = arr.erase(arr.cbegin() + 1);

    EXPECT_EQ(*it, 3);
}