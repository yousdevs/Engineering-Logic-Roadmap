
namespace Core.Entities;

public sealed class TestType
{

    public int Id { get; private set; }
    public string Title { get; private set; }
    public string Description { get; private set; }
    public Money Fee { get; private set; }

    private TestType(int id, string title, string description, Money fee)
    {
        Id = id;
        Title = title;
        Description = description;
        Fee = fee;
    }

    public static TestType Reconstitute(int id, string title, string description, Money fee) => new(id, title, description, fee);

    public void ChangeTitle(string title)
    {
        Guard.RequireNonEmpty(title, nameof(title), "TestType::ChangeTitle");
        Guard.RequireMinLength(title, 3, nameof(title), "TestType::ChangeTitle");
        Guard.RequireMaxLength(title, 100, nameof(title), "TestType::ChangeTitle");

        Title = title;
    }

    public void ChangeDescription(string description)
    {
        Guard.RequireNonEmpty(description, nameof(description), "TestType::ChangeDescription");
        Guard.RequireMinLength(description, 3, nameof(description), "TestType::ChangeDescription");
        Guard.RequireMaxLength(description, 500, nameof(description), "TestType::ChangeDescription");

        Description = description;
    }

    public void ChangeFee(Money fee)
    {

        Fee = fee;
    }
}
