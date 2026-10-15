namespace DSA.Core.Datastructures;

public sealed class AVLTree<T> where T : IComparable<T>
{
    
    public bool Insert(T value)
    {
        if(_root == null)
        {
            _root = new Node(value);
            Count++;
            return true;
        }

        Node? current = _root;
        var path = new Stack<(Node node, bool wentLeft)>();

        while(current != null)
        {
            int cmp = value.CompareTo(current.Value);

            if(cmp < 0)
            {
                path.Push((current!, true));
                current = current.Left;
            }else if(cmp > 0)
            {
                path.Push((current!, false));
                current = current.Right;
            }
            else
            {
                return false; // duplicate
            }
        }

        // current now is null, parent and direction are top of the stack
        var insertionParent = path.Peek();
        if (insertionParent.wentLeft)
        {
            insertionParent.node.Left = new Node(value);
        }
        else
        {
            insertionParent.node.Right = new Node(value);
        }
        Count++;

        // value inserted, now we pop the stack, update heights and balance each parent

        while(path.Count > 0)
        {
            var (node, _) = path.Pop();
            UpdateHeight(node);

            var newSubtreeRoot = Balance(node);
            if(path.Count > 0)
            {
                var (parent, parentWentLeft) = path.Peek();
                if (parentWentLeft)
                {
                    parent.Left = newSubtreeRoot;
                }
                else
                {
                    parent.Right = newSubtreeRoot;
                }
            }
            else
            {
                _root = newSubtreeRoot; // no parent, this is the new root.
            }
        }

        return true;
    }

    public bool Search(T value)
    {
        
        Node? current = _root;

        while(current != null)
        {
            int cmp = value.CompareTo(current.Value);

            if(cmp < 0)
            {
                current = current.Left;
            }else if(cmp > 0)
            {
                current = current.Right;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
    
    private void RebalancePath(Stack<(Node parent, bool wentLeft)> path)
    {
        while(path.Count > 0)
        {
            var (node, _) = path.Pop();
            UpdateHeight(node);
            var newSubtreeRoot = Balance(node);

            if(path.Count > 0)
            {
                var (parent, parentWentLeft) = path.Peek();
                if(parentWentLeft)
                    parent.Left = newSubtreeRoot;
                else
                    parent.Right = newSubtreeRoot;
            }
            else
            {
                _root = newSubtreeRoot;
            }
        }
    }
    public bool Delete(T value)
    {
        Node? current = _root;
        var path = new Stack<(Node parent, bool wentLeft)>();

        while(current != null)
        {
            int cmp = value.CompareTo(current.Value);

            if(cmp < 0)
            {
                path.Push((current, true));
                current = current.Left;
            }else if(cmp > 0)
            {
                path.Push((current, false));
                current = current.Right;
            }
            else
            {
                
                // 3 cases:
                
                // case 1: node is leaf
                if(current.Left == null && current.Right == null)
                {
                    if(path.Count == 0)
                    {
                        _root = null;
                        Count--;
                        return true;
                    }
                    var (parent, wentLeft) = path.Peek();
                    if (wentLeft)
                        parent.Left = null;
                    else
                        parent.Right = null;
                    
                    Count--;
                    
                    RebalancePath(path);
                    
                    return true;
                }


                // Case 2: one child
                if(current.Left == null || current.Right == null)
                {
                    Node? child = current.Left ?? current.Right;
                    
                    // replace current with child, parent point to child directly
                    if(path.Count == 0)
                    {
                        _root = child;
                        Count--;
                        return true;
                    }
                    var (parent, wentLeft) = path.Peek();
                    if (wentLeft)
                        parent.Left = child;
                    else
                        parent.Right = child;
                    
                    Count --;
                    RebalancePath(path);
                    return true;
                }

                // Case 3: two children

                Node nodeToCopyTo = current;
                path.Push((current, false));
                current = current.Right;
                while (current.Left != null)
                {
                    path.Push((current!, true));
                    current = current!.Left;
                }

                var (successorParent, successorWentLeft) = path.Peek(); // or _root if stack empty

                // successor has no left child, may have right
                nodeToCopyTo.Value = current.Value;
                Node? successorChild = current.Right;

                if(successorWentLeft)
                    successorParent.Left = successorChild;
                else
                    successorParent.Right = successorChild;
                    
                Count--;
                RebalancePath(path);
                return true;

            }
        }
        
        return false;
    }
    private sealed class Node
    {
        public Node? Left{get; set;}
        public T Value{get; set;}
        public Node? Right{get; set;}

        public int Height{get; set;}
        public Node(T value)
        {
            Value = value;
            Height = 1; // new node has no childrens yet, the hieght is 1 (the node itself)
        }
    }

    private static int HeightOf(Node? node) => node?.Height ?? 0;
    private static void UpdateHeight(Node node) => node.Height = 1 + Math.Max(HeightOf(node.Left), HeightOf(node.Right));

    private static Node RotateRight(Node z)
    {
        //     bf(z) > 1  AND  bf(z.Left) >= 0

        //         z                y
        //        /                / \
        //      y       →         x   z
        //     /
        //    x

        Node y = z.Left!;

        z.Left = y.Right;
        y.Right = z;
        
        UpdateHeight(z);
        UpdateHeight(y);

        return y;
    }

    private static Node RotateLeft(Node z)
    {
            // bf(z) < -1  AND  bf(z.Right) <= 0
            //     z                  y
            //      \                / \
            //       y      →       z   x
            //        \
            //         x

        Node y = z.Right!;
        z.Right = y.Left;
        y.Left = z;
        
        UpdateHeight(z);
        UpdateHeight(y);
        
        return y;
    }

    private static Node Balance(Node z)
    {
        // case 1, single right rotation
        //     bf(z) > 1  AND  bf(z.Left) >= 0

        //     z                y
        //    /                / \
        //   y        →       x   z
        //  /
        // x

        if(BalanceFactor(z) > 1 && BalanceFactor(z.Left!) >= 0)
        {
            return RotateRight(z);
        }

        // case 2, single left rotation
        // bf(z) < -1  AND  bf(z.Right) <= 0
            //     z                  y
            //      \                / \
            //       y      →       z   x
            //        \
            //         x

        if(BalanceFactor(z) < -1 && BalanceFactor(z.Right!) <= 0)
        {
            return RotateLeft(z);
        }

        // case 3, left-right double rotation
        //     bf(z) > 1  AND  bf(z.Left) < 0

        //       z                z              x
        //      /                /              / \
        //     y        →       x      →       y   z
        //      \               /
        //       x             y

        if(BalanceFactor(z) > 1 && BalanceFactor(z.Left!) < 0)
        {
            z.Left = RotateLeft(z.Left!);
            return RotateRight(z);
        }

        // case 4, right-left double rotation
        //     bf(z) < -1  AND  bf(z.Right) > 0

        // z                z                x
        //  \                \              / \
        //   y      →         x     →      z   y
        //  /                  \
        // x                    y

        if(BalanceFactor(z) < -1 && BalanceFactor(z.Right!) > 0)
        {
            z.Right = RotateRight(z.Right!);
            return RotateLeft(z);
        }

        return z; // already balanced.
    }
    private static int BalanceFactor(Node node) => HeightOf(node.Left) - HeightOf(node.Right);
    private Node? _root;

    public int Count{get; private set;}
}