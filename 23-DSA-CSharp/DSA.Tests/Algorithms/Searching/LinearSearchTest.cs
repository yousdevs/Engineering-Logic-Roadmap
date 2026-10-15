using DSA.Core.Algorithms;
namespace DSA.Tests.Algorithms;

public class LinearSearchTest
{
    
    [Fact]
    public void Search_WhenTargetExists_ReturnCorrectIndex()
    {
        int[] arr = {1, 2, 5, 4};
        Assert.Equal(3, LinearSearch.Search(arr, 4));
    }

    [Fact]
    public void Search_WhenTargetDoesNotExists_ReturnNegativeOne()
    {
        int[] arr = {3, 5, 4};
        Assert.Equal(-1, LinearSearch.Search(arr, 10));
    }

    [Fact]
    public void Search_WhenArrayEmpty_ReturnNegativeOne()
    {
        Assert.Equal(-1, LinearSearch.Search([], 3));
    }
}