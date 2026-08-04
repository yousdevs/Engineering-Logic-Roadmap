namespace Core.DTOs;

public sealed record Page
{
    public int Number { get; }
    public int Size { get; }

    public Page(int number, int size)
    {

        if (number < 1)
            throw new ArgumentException("Page number must be greater than 0.", nameof(number));

        if (size < 1 || size > 100)
            throw new ArgumentException("Page size must be between 1 and 100.", nameof(size));

        Number = number;
        Size = size;
    }
}




public sealed record PagedResult<T>(

    IReadOnlyList<T> Items,
    int TotalCount,
    int Page,
    int PageSize
    );