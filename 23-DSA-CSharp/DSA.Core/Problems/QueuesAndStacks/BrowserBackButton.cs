namespace DSA.Core.Problems.QueuesAndStacks;

public class BrowserBackButton
{
    private readonly Stack<string> _history = new();

    public void Visit(string url) => _history.Push(url);

    public string GoBack() => _history.Count > 0 ? _history.Pop() : "No history";
}