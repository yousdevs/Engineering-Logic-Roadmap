namespace DSA.Tests.Datastructures;

using DSA.Core.Datastructures;
using Xunit;

public class GraphTests
{
    
    [Fact]
    public void AddNode_DuplicateReturnsFalse_NodeCountUnchanged()
    {
        var graph = new Graph<string>(false);

        graph.AddNode("A");

        Assert.False(graph.AddNode("A"));
        Assert.Equal(1, graph.NodeCount);
    }

    [Fact]
    public void AddEdge_MissingNodeReturnsFalse()
    {
        var graph = new Graph<string>(false);

        graph.AddNode("A");

        Assert.False(graph.AddEdge("A", "C"));
        Assert.Equal(0, graph.EdgeCount);
    }

    [Fact]
    public void AddEdge_ValidEdgeIncrementsEdgeCount()
    {
        var graph = new Graph<string>(false);

        graph.AddNode("A");
        graph.AddNode("B");

        Assert.True(graph.AddEdge("A", "B"));
        Assert.Equal(1, graph.EdgeCount);
    }

    [Fact]
    public void BFS_VisitsInCorrectLevelOrder()
    {
        var graph = new Graph<string>(false);

        graph.AddNode("A");
        graph.AddNode("B");
        graph.AddNode("C");
        graph.AddNode("D");
    

        graph.AddEdge("A", "B");
        graph.AddEdge("A", "C");
        graph.AddEdge("B", "D");

        Assert.Equal(["A", "B", "C", "D"], graph.BFS("A").ToArray());
    }

    [Fact] public void DFS_GoesDeepBeforeWide()
    {
        var graph = new Graph<string>(false);

        graph.AddNode("A");
        graph.AddNode("B");
        graph.AddNode("C");
        graph.AddNode("D");
    

        graph.AddEdge("A", "B");
        graph.AddEdge("A", "C");
        graph.AddEdge("B", "D");

        Assert.Equal(["A", "C", "B", "D"], graph.DFS("A").ToArray());
    }

    [Fact]
    public void Directed_EdgeABThenBCannotReachA()
    {
        var graph = new Graph<string>(true);

        graph.AddNode("A");
        graph.AddNode("B");

        graph.AddEdge("A", "B");

        Assert.Equal(["A", "B"], graph.BFS("A").ToArray());
        Assert.Equal(["B"], graph.BFS("B").ToArray());
    }
}