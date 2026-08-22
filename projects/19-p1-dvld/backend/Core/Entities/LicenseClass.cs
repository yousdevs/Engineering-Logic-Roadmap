namespace Core.Entities;

public sealed class LicenseClass
{

    public int Id { get; internal set; }
    public string Title { get; private set; }
    public string Description { get; private set; }
    public int MinimumAllowedAge { get; private set; }
    public int DefaultValidityLength { get; private set; }
    public Money Fee { get; private set; }

    private LicenseClass(int id, string title, string description, int minimumAllowedAge, int defaultValidityLength, Money fee)
    {
        Id = id;
        Title = title;
        Description = description;
        MinimumAllowedAge = minimumAllowedAge;
        DefaultValidityLength = defaultValidityLength;
        Fee = fee;
    }

    public static LicenseClass Reconstitute(int id, string title, string description, int minimumAllowedAge, int defaultValidityLength, Money fee)
    {

        return new LicenseClass(id, title, description, minimumAllowedAge, defaultValidityLength, fee);
    }


}