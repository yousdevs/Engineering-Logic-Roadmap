namespace Core.Entities;

public enum ApplicationTypeId
{
    NewLocalDrivingLicense = 1,
    RenewDrivingLicense = 2,
    ReplacementLost = 3,
    ReplacementDamaged = 4,
    ReleaseDetained = 5,
    NewInternationalLicense = 6,
    RetakeTest = 7
}
public sealed class ApplicationType
{

    public ApplicationTypeId Id { get; internal set; }
    public string Title { get; private set; }
    public Money Fee { get; private set; }


    private ApplicationType(ApplicationTypeId id, string title, Money fee)
    {
        Id = id;
        Title = title;
        Fee = fee;
    }

    public static ApplicationType Reconstitute(ApplicationTypeId id, string title, Money fee) => new(id, title, fee);

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

    public bool RequiresLicenseClass => Id is ApplicationTypeId.NewLocalDrivingLicense || Id is ApplicationTypeId.RenewDrivingLicense;
}
