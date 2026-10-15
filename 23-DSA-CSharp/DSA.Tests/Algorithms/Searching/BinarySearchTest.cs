using DSA.Core.Algorithms;

namespace DSA.Tests.Algorithms;

public class BinarySearchTest
{
    
    [Fact]
    public void Search_WhenTargetExists_ReturnCorrectIndex()
    {
        int[] arr = { 22, 25, 37, 41, 45,46, 49, 51,55,58,70,80,82,90,95 };
        Assert.Equal(3, BinarySearch.Search(arr, 41));
    }

    [Fact]
    public void Search_WhenTargetDoesNotExists_ReturnNegativeOne()
    {
        int[] arr = { 22, 25, 37, 41, 45,46, 49, 51,55,58,70,80,82,90,95 };
        Assert.Equal(-1, BinarySearch.Search(arr, 100));
    }

    [Fact]
    public void Search_WhenArrayEmpty_ReturnNegativeOne()
    {
        Assert.Equal(-1, BinarySearch.Search([], 3));
    }
}