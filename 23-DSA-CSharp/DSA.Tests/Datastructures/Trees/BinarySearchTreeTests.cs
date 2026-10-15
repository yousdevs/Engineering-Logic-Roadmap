namespace DSA.Tests.Datastructures;

using DSA.Core.Datastructures;
using Xunit;

public class BinarySearchTreeTests
{
    
    [Fact]
    public void InsertSingle_SearchFindsIt()
    {
        var tree = new BinarySearchTree<int>();

        tree.Insert(2);

        Assert.True( tree.Search(2));
    }

    [Fact]
    public void InsertSeveral_SearchFindsAll()
    {
        var tree = new BinarySearchTree<int>();

        tree.Insert(5);
        tree.Insert(4);
        tree.Insert(2);
    
        Assert.True( tree.Search(2));
        Assert.True( tree.Search(4));
        Assert.True( tree.Search(5));
    }

    [Fact]
    public void Search_MissingValueReturnsFalse()
    {
        var tree = new BinarySearchTree<int>();

        tree.Insert(5);
        tree.Insert(4);
        tree.Insert(2);

        Assert.False( tree.Search(7));
    }

    [Fact]
    public void Insert_DuplicateReturnsFalseAndCountUnchanged()
    {
        var tree = new BinarySearchTree<int>();

        tree.Insert(5);
        
        Assert.False(tree.Insert(5));
        Assert.Equal(1, tree.Count);
    }

    [Fact]
    public void InOrder_yieldsInAcendingOrder()
    {
        var tree = new BinarySearchTree<int>();

        tree.Insert(5); tree.Insert(3); tree.Insert(7);  tree.Insert(1);tree.Insert(4);

        var iter = tree.InOrder();
        Assert.Equal([1, 3, 4, 5, 7], iter.ToArray());
    }

    [Fact]
    public void Search_WorksInSortedInsertion()
    {
        var tree = new BinarySearchTree<int>();
        tree.Insert(1);
        tree.Insert(2);
        tree.Insert(3);

        Assert.True(tree.Search(3));
    }

    [Fact]
    public void Search_EmptyTreeReturnsFalse()
    {
        var tree = new BinarySearchTree<int>();

        Assert.False(tree.Search(4));
    }
}