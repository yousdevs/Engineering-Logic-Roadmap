namespace Core.Entities;

public enum LicenseIssueReason
{
    FirstTime = 1,
    Renew = 2,
}
public sealed class License
{
    public int Id { get; internal set; }
    public int ApplicationId { get; private set; }
    public int DriverId { get; private set; }
    public int LicenseClassId { get; private set; }
    public DateTime IssuedAt { get; private set; }
    public DateTime ExpiresAt { get; private set; }
    public string? Notes { get; private set; }
    public Money PaidFees { get; private set; }
    public bool IsActive { get; private set; }
    public LicenseIssueReason IssueReason { get; private set; }
    public int CreatedByUserId { get; private set; }


    private License(int id, int applicationId, int driverId, int licenseClassId, DateTime issuedAt, DateTime expiresAt, string? notes, Money paidFees, bool isActive, LicenseIssueReason issueReason, int createdByUserId)
    {
        Id = id;
        ApplicationId = applicationId;
        DriverId = driverId;
        LicenseClassId = licenseClassId;
        IssuedAt = issuedAt;
        ExpiresAt = expiresAt;
        Notes = notes;
        PaidFees = paidFees;
        IsActive = isActive;
        IssueReason = issueReason;
        CreatedByUserId = createdByUserId;
    }

    public static License Issue(int applicationId, int driverId, LicenseClass licenseClass, string? notes, LicenseIssueReason issueReason, int createdByUserId)
    {

        var validityYears = licenseClass.DefaultValidityLength;
        var now = DateTime.UtcNow;
        var expiresAt = now.AddYears(validityYears);
        var paidFees = licenseClass.Fee;

        return new License(-1, applicationId, driverId, licenseClass.Id, now, expiresAt, notes, paidFees, true, issueReason, createdByUserId);
    }

    public static License Reconstitute(int id, int applicationId, int driverId, int licenseClassId, DateTime issuedAt, DateTime expiresAt, string? notes, Money paidFees, bool isActive, LicenseIssueReason issueReason, int createdByUserId)
    {

        return new License(id, applicationId, driverId, licenseClassId, issuedAt, expiresAt, notes, paidFees, isActive, issueReason, createdByUserId);
    }

    public void DeActivate()
    {
        if (!IsActive)
            throw new InvalidOperationException("Already inactive.");
        IsActive = false;
    }


}
