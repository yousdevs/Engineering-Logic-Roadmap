namespace DSA.Core.Datastructures;

public sealed class Graph<T> where T : notnull
{
    
    public int EdgeCount{get; private set;}
    public int NodeCount{get; private set;}

    public Graph(bool isDirected)
    {
        _isDirected = isDirected;
        _nodes = new Dictionary<T, Node>();
        EdgeCount = 0;
        NodeCount = 0;
    }

    public bool AddNode(T value) // true added, false duplicate
    {
        if(_nodes.ContainsKey(value))
            return false;
        
        _nodes.Add(value, new Node(value));
        NodeCount++;
        return true;
    }

    public bool AddEdge(T from, T to, double weight = 1.0) // true added, false node not found.
    {
        if(!_nodes.ContainsKey(from) || !_nodes.ContainsKey(to))
            return false;

        if (_isDirected)
        {
            _nodes[from].Neighbors.Add((_nodes[to], weight));
        }
        else
        {
            _nodes[from].Neighbors.Add((_nodes[to], weight));
            _nodes[to].Neighbors.Add((_nodes[from], weight));
        }

        EdgeCount++;
        return true;
    }

    public IEnumerable<T> BFS(T start)
    {

        HashSet<Node> visited = new HashSet<Node>();
        Queue<Node> path = new Queue<Node>();

        path.Enqueue(_nodes[start]);
        visited.Add(_nodes[start]);

        while(path.Count > 0)
        {
            Node currentNode = path.Dequeue();
            
            foreach((Node node, double _) in currentNode.Neighbors)
            {
                if(visited.Contains(node))
                    continue;
                path.Enqueue(node);
                visited.Add(node);
            }

            yield return currentNode.Value;
        }
    }

    public IEnumerable<T> DFS(T start)
    {
        
        HashSet<Node> visited = new HashSet<Node>();
        Stack<Node> path = new Stack<Node>();
        path.Push(_nodes[start]);
        
        while(path.Count > 0)
        {
            Node currentNode = path.Pop();

            if(visited.Contains(currentNode))
                continue;
            
            visited.Add(currentNode);
            yield return currentNode.Value;

            foreach((Node neighbor, double _) in currentNode.Neighbors)
            {
                if(!visited.Contains(neighbor))
                    path.Push(neighbor);
            }
        }

    }

    private readonly bool _isDirected;
    private readonly Dictionary<T, Node> _nodes;



    private sealed class Node
    {
        public T Value {get; set;}
        public List<(Node Neighbor, double Weight)> Neighbors {get; set;}

        public Node(T value)
        {
            Value = value;
            Neighbors = new List<(Node Neighbor, double Weight)>();
        }
    }
}