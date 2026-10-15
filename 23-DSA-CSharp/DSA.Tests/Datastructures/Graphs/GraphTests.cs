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

    [Fact]
    public void Dijkstra_ShortestDistanceIsCorrectOnSimpleWeightedGraph()
    {
        var graph = new Graph<string>(true);
        graph.AddNode("A");
        graph.AddNode("B");
        graph.AddNode("C");
        graph.AddNode("D");

        graph.AddEdge("A", "B", 2);
        graph.AddEdge("A", "C", 1);
        graph.AddEdge("B", "D", 1);
        graph.AddEdge("C", "D", 5);

        var result = graph.Dijkstra("A");
        Assert.Equal(3, result.Distances["D"]);
    }

    [Fact]
    public void Dijkstra_TryGetPathReturnsCorrectSequence()
    {
        var graph = new Graph<string>(true);
        graph.AddNode("A");
        graph.AddNode("B");
        graph.AddNode("C");
        graph.AddNode("D");

        graph.AddEdge("A", "B", 2);
        graph.AddEdge("A", "C", 1);
        graph.AddEdge("B", "D", 1);
        graph.AddEdge("C", "D", 5);

        var result = graph.Dijkstra("A");
        result.TryGetPath("D", out IEnumerable<string> path);
        Assert.Equal(["A", "B", "D"], path);
    }

    [Fact]
    public void Dijkstra_UnreachableNodeReturnsFalseFromTryGetPath()
    {
        var graph = new Graph<string>(true);
        graph.AddNode("A");
        graph.AddNode("B");
        graph.AddNode("C");
        graph.AddNode("D");
        graph.AddNode("E");

        graph.AddEdge("A", "B", 2);
        graph.AddEdge("A", "C", 1);
        graph.AddEdge("B", "D", 1);
        graph.AddEdge("C", "D", 5);

        var result = graph.Dijkstra("A");
        bool reachable = result.TryGetPath("E", out IEnumerable<string> path);
        Assert.False(reachable);
    }

    [Fact]
    public void Dijkstra_StartNodeNotInGraphThrowsArgumentException()
    {
        var graph = new Graph<string>(true);
        graph.AddNode("A");
        graph.AddNode("B");
        graph.AddNode("C");
        graph.AddNode("D");

        graph.AddEdge("A", "B", 2);
        graph.AddEdge("A", "C", 1);
        graph.AddEdge("B", "D", 1);
        graph.AddEdge("C", "D", 5);

        Assert.Throws<ArgumentException>(() => graph.Dijkstra("F"));
    }

    [Fact]
    public void Dijkstra_TryGetPath_StartNodeReturnsItself()
    {
        var graph = new Graph<string>(true);
        graph.AddNode("A");
        graph.AddNode("B");
        graph.AddEdge("A", "B", 1);

        var result = graph.Dijkstra("A");
        result.TryGetPath("A", out IEnumerable<string> path);
        Assert.Equal(["A"], path.ToArray());
    }
}