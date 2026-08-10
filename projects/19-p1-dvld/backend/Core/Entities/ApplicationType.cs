namespace Core.Entities;

public sealed class ApplicationType
{

    public int Id { get; internal set; }
    public string Title { get; private set; }
    public Money Fee { get; private set; }


    private ApplicationType(int id, string title, Money fee)
    {
        Id = id;
        Title = title;
        Fee = fee;
    }

    public static ApplicationType Reconstitute(int id, string title, Money fee) => new(id, title, fee);

    public void ChangeTitle(string newTitle)
    {
        Guard.RequireNonEmpty(newTitle, nameof(newTitle), "ApplicationType::ChangeTitle");
        Guard.RequireMinLength(newTitle, 3, nameof(newTitle), "ApplicationType::ChangeTitle");

        Title = newTitle;
    }

    public void ChangeFee(Money fee)
    {

        Fee = fee;
    }
}
