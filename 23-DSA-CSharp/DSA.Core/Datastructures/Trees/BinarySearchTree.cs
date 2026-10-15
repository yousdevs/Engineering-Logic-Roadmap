using System.Runtime.InteropServices;

namespace DSA.Core.Datastructures;
public sealed class BinarySearchTree<T> where T : IComparable<T>
{
    
    public int Count{get; private set;}

    public bool Insert(T value)
    {

        if(_root == null)
            {
                _root = new Node(value);
                Count++;
                return true;
            }

        Node current = _root;
        
        while (true)
        {

            int cmp  = value.CompareTo(current.Value);
            if( cmp  < 0)
            {
                if(current.Left == null)
                {
                    current.Left = new Node(value);
                    Count++;
                    return true;
                }
                current = current.Left;
            }
            else if(cmp  > 0)
            {
                if(current.Right == null)
                {
                    current.Right = new Node(value);
                    Count++;
                    return true;
                }
                current = current.Right;
            }
            else 
            {
                return false; // duplicate
            }
        }
    }

    public bool Search(T value)
    {
        
        var current = _root;

        while(current != null)
        {
            int cmp = value.CompareTo(current.Value);

            if(cmp < 0)
            {
                current = current.Left;
            }
            else if(cmp > 0)
            {
                current = current.Right;
            }
            else { return true;}

            
        }
        return false;
        
    }

    public IEnumerable<T> InOrder()
    {
        var current = _root;
        var stack = new Stack<Node>();

        while (true)
        {
            while(current != null)
            {
                stack.Push(current);
                current = current.Left; 
            }

            if(stack.Count == 0)
                break;
            
            current = stack.Pop();
            yield return current.Value;

            current = current.Right;
        }
    }
    
    private sealed class Node
    {
        public Node? Left {get; set;}
        public Node? Right {get; set;}
        public T Value {get;}
        public Node(T value)
        {
            Value = value;
        }
    }
    
    private Node? _root;
}