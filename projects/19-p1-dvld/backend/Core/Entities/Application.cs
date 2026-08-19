namespace Core.Entities;

public enum ApplicationStatus
{
    New = 1,
    Cancelled = 2,
    Completed = 3
}
public sealed class Application
{

    public int Id { get; internal set; }
    public int PersonId { get; private set; }
    public ApplicationTypeId ApplicationTypeId { get; private set; }
    public int CreatedByUserId { get; private set; }
    public DateTime CreatedAt { get; private set; }
    public ApplicationStatus Status { get; private set; }
    public DateTime LastStatusAt { get; private set; }
    public Money PaidFees { get; private set; }


    private Application(int id, int personId, ApplicationTypeId applicationTypeId, int createdByUserId, DateTime createdAt, ApplicationStatus status, DateTime lastStatusAt, Money paidFees)
    {
        Id = id;
        PersonId = personId;
        ApplicationTypeId = applicationTypeId;
        CreatedByUserId = createdByUserId;
        CreatedAt = createdAt;
        Status = status;
        LastStatusAt = lastStatusAt;
        PaidFees = paidFees;
    }

    public static Application CreateNewLocalDrivingLicense(int personId, DateTime personDateOfBirth, ApplicationType applicationType, LicenseClass licenseClass, int createdByUserId)
    {

        if (applicationType.Id != ApplicationTypeId.NewLocalDrivingLicense)
            throw new ArgumentException(
                "ApplicationType does not meet required application type.",
                nameof(applicationType));

        DateTime now = DateTime.UtcNow;
        if (CalculateAge(personDateOfBirth, now) < licenseClass.MinimumAllowedAge)
            throw new InvalidOperationException("Person age does not meet required min age for this class application.");

        Money paidFee = applicationType.Fee + licenseClass.Fee;

        return new Application(-1, personId, ApplicationTypeId.NewLocalDrivingLicense, createdByUserId, now, ApplicationStatus.New, now, paidFee);
    }

    public static Application CreateRetakeTest(int personId, int createdByUserId, ApplicationType applicationType)
    {

        if (applicationType.Id != ApplicationTypeId.RetakeTest)
            throw new ArgumentException(
                "ApplicationType does not meet required application type.",
                nameof(applicationType));

        DateTime now = DateTime.UtcNow;

        return new Application(-1, personId, ApplicationTypeId.RetakeTest, createdByUserId, now, ApplicationStatus.Completed, now, applicationType.Fee);
    }

    public static Application CreateInternationalLicense(int personId, int createdByUserId, Money paidFees)
    {

        var now = DateTime.UtcNow;
        return new Application(-1, personId, ApplicationTypeId.NewInternationalLicense, createdByUserId, now, ApplicationStatus.Completed, now, paidFees);
    }

    public static Application CreateRenewLocalLicense(int personId, int createdByUserId, ApplicationType applicationType, LicenseClass licenseClass)
    {

        if (applicationType.Id != ApplicationTypeId.RenewDrivingLicense)
            throw new ArgumentException(
                "ApplicationType does not meet required application type.",
                nameof(applicationType));

        var paidFees = applicationType.Fee + licenseClass.Fee;
        var now = DateTime.UtcNow;
        return new Application(-1, personId, ApplicationTypeId.RenewDrivingLicense, createdByUserId, now, ApplicationStatus.Completed, now, paidFees);
    }

    private static int CalculateAge(DateTime dateOfBirth, DateTime asOf)
    {
        int age = asOf.Year - dateOfBirth.Year;
        if (dateOfBirth.Date > asOf.Date.AddYears(-age))
            age--;

        return age;
    }
    public static Application Reconstitute(int applicationId, int personId, ApplicationTypeId applicationTypeId, int createdByUserId, DateTime createdAt, ApplicationStatus status, DateTime lastStatusAt, Money paidFees)
    {
        return new Application(applicationId, personId, applicationTypeId, createdByUserId, createdAt, status, lastStatusAt, paidFees);
    }

    public void Cancel()
    {
        if (Status == ApplicationStatus.Completed)
            throw new InvalidOperationException("Cant cancel a completed application.");

        if (Status == ApplicationStatus.Cancelled)
            throw new InvalidOperationException("Application already cancelled.");

        Status = ApplicationStatus.Cancelled;
        LastStatusAt = DateTime.UtcNow;

    }

    public void Complete()
    {
        if (Status == ApplicationStatus.Completed)
            throw new InvalidOperationException("Application already completed.");

        if (Status == ApplicationStatus.Cancelled)
            throw new InvalidOperationException("Cant complete cancelled application.");

        Status = ApplicationStatus.Completed;
        LastStatusAt = DateTime.UtcNow;
    }
}
