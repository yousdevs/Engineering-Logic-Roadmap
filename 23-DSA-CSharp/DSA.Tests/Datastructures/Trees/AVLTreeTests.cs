namespace DSA.Tests.Datastructures;
using DSA.Core.Datastructures;
using Xunit;

public class AVLTreeTests
{
    
    [Fact]
    public void Insert_DuplicateReturnsFalseAndCountUnchanged()
    {
        AVLTree<int> tree = new AVLTree<int>();

        tree.Insert(1);

        Assert.False(tree.Insert(1));
        Assert.Equal(1, tree.Count); 
    }

    [Fact]
    public void InsertSingle_SearchFindsIt()
    {
        AVLTree<int> tree = new AVLTree<int>();

        tree.Insert(1);

        Assert.True(tree.Search(1)); 
    }

    [Fact]
    public void Delete_DeleteValue_SearchSameValueReturnFalse()
    {
        AVLTree<int> tree = new AVLTree<int>();

        tree.Insert(1);

        Assert.True(tree.Delete(1));
        Assert.Equal(0, tree.Count);
        Assert.False(tree.Search(1));
    }
}