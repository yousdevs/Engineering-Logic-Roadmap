using Core.Entities;
using Data;

namespace Core.Services;

public sealed class LicenseService
{

    private readonly ICurrentUser _currentUser;

    public LicenseService(ICurrentUser currentUser)
    {
        _currentUser = currentUser;
    }

    public async Task<int> IssueLocalDrivingLicenseAsync(int applicationId, string? notes)
    {


        var applicationRecord = await ApplicationData.FindByIdAsync(applicationId);
        if (applicationRecord == null)
            throw new KeyNotFoundException($"Application with id={applicationId} does not exist.");

        if ((ApplicationTypeId)applicationRecord.ApplicationTypeId != ApplicationTypeId.NewLocalDrivingLicense)
            throw new InvalidOperationException("Application type does not meet the required type.");

        if ((ApplicationStatus)applicationRecord.ApplicationStatus != ApplicationStatus.New)
            throw new InvalidOperationException("Cannot issue license for cancelled or completed applications.");

        var personId = applicationRecord.ApplicantPersonId;
        if (await LicenseData.ExistsWithSameLicenseClassByPersonId(personId))
            throw new InvalidOperationException("this Person already has License for this license class.");

        var localDrivingLicenseApplicationId = await LocalDrivingLicenseApplicationData.GetIdByApplicationId(applicationId);
        if (localDrivingLicenseApplicationId == null)
            throw new KeyNotFoundException($"LocalDrivingLicenseApplication with applicationId={applicationId} does not exist.");

        var historyRecords = await TestAppointmentData.GetHistoryAsync(localDrivingLicenseApplicationId.Value);

        var attempts = historyRecords.Select(x =>
            new TestAttempt(
                x.TestAppointmentId,
                (TestTypeId)x.TestTypeId,
                x.TestResult.HasValue ? x.TestResult.Value ? TestOutcome.Passed : TestOutcome.Failed : null
        )).ToList();

        var workflow = LocalDrivingLicenseTestWorkflow.FromAttempts(attempts);

        if (!workflow.CanIssueLicense)
            throw new InvalidOperationException("Cannot Issue License before passing all tests.");

        var licenseClassId = await LocalDrivingLicenseApplicationData.GetLicenseClassIdByApplicationIdAsync(applicationId);

        var licenseClassRecord = await LicenseClassData.FindByIdAsync(licenseClassId);
        if (licenseClassRecord == null)
            throw new KeyNotFoundException($"LicenseClass with id={licenseClassId} does not exist.");

        var licenseClass = LicenseClass.Reconstitute(
            licenseClassRecord.Id!,
            licenseClassRecord.Title,
            licenseClassRecord.Description,
            licenseClassRecord.MinAge,
            licenseClassRecord.ValidityLengthYears,
            Money.From(licenseClassRecord.Fees)
            );

        var driverId = await DriverData.GetIdByPersonIdAsync(personId);
        if (driverId == null)
            driverId = await DriverData.InsertAsync(new DriverRecord(personId, _currentUser.UserId, DateTime.UtcNow));

        var license = License.Issue(applicationId, driverId.Value, licenseClass, notes, LicenseIssueReason.FirstTime, _currentUser.UserId);

        var application = Application.Reconstitute(

            applicationId,
            applicationRecord.ApplicantPersonId,
            (ApplicationTypeId)applicationRecord.ApplicationTypeId,
            applicationRecord.CreatedByUserId,
            applicationRecord.ApplicationDate,
            (ApplicationStatus)applicationRecord.ApplicationStatus,
            applicationRecord.LastStatusDate,
            Money.From(applicationRecord.PaidFees)
            );

        application.Complete();

        var licenseId = await LicenseData.InsertAsync(
            new LicenseRecord(
                license.ApplicationId,
                license.DriverId,
                license.LicenseClassId,
                license.IssuedAt,
                license.ExpiresAt,
                license.Notes,
                license.PaidFees.Amount,
                license.IsActive,
                (int)license.IssueReason,
                license.CreatedByUserId
                )
            );

        await ApplicationData.UpdateByIdAsync(applicationId,
            new ApplicationRecord(
                application.PersonId,
                application.CreatedAt,
                (int)application.ApplicationTypeId,
                (byte)application.Status,
                application.LastStatusAt,
                application.PaidFees.Amount,
                application.CreatedByUserId
                )
            );

        return licenseId;
    }

}
