
using Core.Entities;
using Data;

namespace Core.Services;

public sealed class LicenseDetainmentService
{
    private readonly ICurrentUser _currentUser;

    public LicenseDetainmentService(ICurrentUser currentUser)
    {
        _currentUser = currentUser;
    }


    public async Task<int> DetainLicenseAsync(int licenseId, Money fineFees)
    {

        var licenseRecord = await LicenseData.FindByIdAsync(licenseId);

        if (licenseRecord == null)
            throw new KeyNotFoundException(nameof(licenseId));

        var license = License.Reconstitute(
            licenseRecord.Id,
            licenseRecord.ApplicationId,
            licenseRecord.DriverId,
            licenseRecord.LicenseClassId,
            licenseRecord.IssueDate,
            licenseRecord.ExpirationDate,
            licenseRecord.Notes,
            Money.From(licenseRecord.PaidFees),
            licenseRecord.IsActive,
            (LicenseIssueReason)licenseRecord.IssueReason,
            licenseRecord.CreatedByUserId
            );

        license.DeActivate();

        var LicenseDeatainRecord = new DetainedLicenseRecord(
            -1,
            license.Id,
            DateTime.UtcNow,
            fineFees.Amount,
            _currentUser.UserId,
            false,
            null,
            null,
            null
            );

        bool licenseUpdated = await LicenseData.UpdateAsync(

            new LicenseRecord(
                license.Id,
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
        if (!licenseUpdated)
            throw new InvalidOperationException("Failed to update license.");

        var detainId = await DetainedLicenseData.InsertAsync(LicenseDeatainRecord);
        return detainId;
    }

    public async Task ReleaseDatainedLicenseAsync(int licenseId)
    {

        var licenseRecord = await LicenseData.FindByIdAsync(licenseId);

        if (licenseRecord == null)
            throw new KeyNotFoundException(nameof(licenseId));

        var license = License.Reconstitute(
            licenseRecord.Id,
            licenseRecord.ApplicationId,
            licenseRecord.DriverId,
            licenseRecord.LicenseClassId,
            licenseRecord.IssueDate,
            licenseRecord.ExpirationDate,
            licenseRecord.Notes,
            Money.From(licenseRecord.PaidFees),
            licenseRecord.IsActive,
            (LicenseIssueReason)licenseRecord.IssueReason,
            licenseRecord.CreatedByUserId
            );



        var personId = await DriverData.GetPersonIdByIdAsync(license.DriverId);

        var detainedLicense = await DetainedLicenseData.FindByLicenseIdAsync(licenseId);
        if (detainedLicense == null)
            throw new KeyNotFoundException(nameof(detainedLicense));


        var application = Application.CreateReleaseDetainedLicense(personId, _currentUser.UserId, Money.From(detainedLicense.FineFees));

        license.Activate();

        await LicenseData.UpdateAsync(
            new LicenseRecord(
                license.Id,
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

        int? applicationId = await ApplicationData.InsertAsync(
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

        await DetainedLicenseData.UpdateAsync(
            new DetainedLicenseRecord(
                detainedLicense.Id,
                detainedLicense.LicenseId,
                detainedLicense.DetainDate,
                detainedLicense.FineFees,
                detainedLicense.CreatedByUserId,
                true,
                DateTime.UtcNow,
                _currentUser.UserId,
                applicationId!.Value
                )
            );
    }
}
