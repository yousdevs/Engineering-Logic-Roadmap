namespace Core.Entities;

public sealed class InternationalLicense
{
    public int Id { get; internal set; }
    public int ApplicationId { get; private set; }
    public int DriverId { get; private set; }
    public int IssuedByLocalLicenseId { get; private set; }
    public DateTime IssuedAt { get; private set; }
    public DateTime ExpiresAt { get; private set; }
    public bool IsActive { get; private set; }
    public int CreateByUserId { get; private set; }

    private InternationalLicense(int id, int applicationId, int driverId, int issuedByLocalLicenseId, DateTime issuedAt, DateTime expiresAt, bool isActive, int createByUserId)
    {
        Id = id;
        ApplicationId = applicationId;
        DriverId = driverId;
        IssuedByLocalLicenseId = issuedByLocalLicenseId;
        IssuedAt = issuedAt;
        ExpiresAt = expiresAt;
        IsActive = isActive;
        CreateByUserId = createByUserId;
    }

    public static InternationalLicense Issue(int applicationId, int driverId, int issuedByLocalLicenseId, int validatyYears, int createdByUserId)
    {

        if (validatyYears < 1)
            throw new ArgumentException("Validaty must be at least 1 years.", nameof(validatyYears));

        var now = DateTime.UtcNow;
        var expiresAt = now.AddYears(validatyYears);


        return new InternationalLicense(-1, applicationId, driverId, issuedByLocalLicenseId, now, expiresAt, true, createdByUserId);
    }

    public void DeActivate()
    {
        if (IsActive)
            throw new InvalidOperationException("Already inactive.");
        IsActive = false;
    }
}
