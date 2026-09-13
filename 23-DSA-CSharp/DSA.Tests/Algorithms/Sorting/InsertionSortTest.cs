using DSA.Core.Algorithms;
using Xunit;

namespace DSA.Tests.Algorithms;

public class InsertionSortTest
{
    
    [Fact]
    public void Sorting_ArraySortedInAscendingOrder()
    {
        int[] arr = {5, 3, 1, 2, 4};

        InsertionSort.Sort(arr);

        Assert.Equal([1, 2, 3, 4, 5], arr);
    }
}