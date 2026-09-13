using DSA.Core.Algorithms;
using Xunit;
namespace DSA.Tests.Algorithms;

public class SelectionSortTest
{
    
    [Fact]
    public void Sorting_ArraySortedInAscendingOrder()
    {
        int[] arr = {5, 3, 4, 1, 2};
        SelectionSort.Sort(arr);
        Assert.Equal([1, 2, 3, 4, 5], arr);
    }
    [Theory]
    [InlineData(new[] { 1, 2, 3, 4, 5 }, new[] { 1, 2, 3, 4, 5 })] // Already sorted
    [InlineData(new[] { 5, 4, 3, 2, 1 }, new[] { 1, 2, 3, 4, 5 })] // Reverse order
    [InlineData(new[] { 3, 1, 3, 2, 1 }, new[] { 1, 1, 2, 3, 3 })] // Duplicates
    [InlineData(new[] { -3, 0, -1, 2 },  new[] { -3, -1, 0, 2 })] // Negative numbers
    [InlineData(new int[] { },           new int[] { })]          // Empty array
    public void Sort_VariousInputArrays_SortsInAscendingOrder(int[] input, int[] expected)
    {
        
        SelectionSort.Sort(input);

        Assert.Equal(expected, input);
    }
}