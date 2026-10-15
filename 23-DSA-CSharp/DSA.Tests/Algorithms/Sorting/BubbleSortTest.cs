using Xunit;
using DSA.Core.Algorithms;

namespace DSA.Tests.Algorithms;

public class BubbleSortTest
{
    [Fact]
    public void Sorting_ArraySortedAscendingOrder()
    {
        int[] arr = {4, 2, 3, 1};
        BubbleSort.Sort(arr);

        Assert.Equal([1, 2, 3, 4], arr);
    }
}