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


    public async Task<int> IssueInternationalLicenseAsync(int localLicenseId)
    {

        var localLicenseRecord = await LicenseData.FindByIdAsync(localLicenseId);

        if (localLicenseRecord == null)
            throw new KeyNotFoundException($"LocalLicense with Id={localLicenseId} does not exist.");


        if (await InternationalLicenseData.ExistActiveByDriverId(localLicenseRecord.DriverId))
            throw new InvalidOperationException("This Driver already has active international license.");

        if (localLicenseRecord.LicenseClassId != 3)
            throw new InvalidOperationException("Class 3 Local License required for International License Issurance.");

        if (!localLicenseRecord.IsActive)
            throw new InvalidOperationException("Active local license required.");

        if (DateTime.UtcNow.AddMonths(6) > localLicenseRecord.ExpirationDate)
            throw new InvalidOperationException("Local license expiration date must be at least 6 months from now.");

        var personId = await ApplicationData.GetPersonIdByApplicationIdAsync(localLicenseRecord.ApplicationId);
        if (personId == null)
            throw new KeyNotFoundException();

        var fees = await ApplicationTypesData.GetFeesByIdAsync((int)ApplicationTypeId.NewInternationalLicense);

        var application = Application.CreateInternationalLicense(personId.Value, _currentUser.UserId, Money.From(fees));

        var applicationId = await ApplicationData.InsertAsync(
            new ApplicationRecord(
                application.PersonId,
                application.CreatedAt,
                (int)application.ApplicationTypeId,
                (byte)application.Status,
                application.LastStatusAt,
                application.PaidFees.Amount,
                application.CreatedByUserId
            ));
        if (applicationId == null)
            throw new InvalidOperationException("Failed to create application.");

        var license = InternationalLicense.Issue(applicationId.Value, localLicenseRecord.DriverId, localLicenseId, 3, _currentUser.UserId);

        var internationalLicenseId = await InternationalLicenseData.InsertAsync(
            new InternationalLicenseRecord(
                    license.ApplicationId,
                    license.DriverId,
                    license.IssuedByLocalLicenseId,
                    license.IssuedAt,
                    license.ExpiresAt,
                    license.IsActive,
                    license.CreateByUserId
                )
            );

        return internationalLicenseId;
    }

    public async Task<int> RenewLocalLicenseAsync(int oldLicenseId, string? notes)
    {

        var oldLicenseRecord = await LicenseData.FindByIdAsync(oldLicenseId);

        if (oldLicenseRecord == null)
            throw new KeyNotFoundException($"License with id={oldLicenseId} does not exist.");

        if (!oldLicenseRecord.IsActive)
            throw new InvalidOperationException("Cannot renew inactive license.");

        if (oldLicenseRecord.ExpirationDate > DateTime.UtcNow)
            throw new InvalidOperationException("Cannot renew unexpired license.");

        var licenseClassRecord = await LicenseClassData.FindByIdAsync(oldLicenseRecord.LicenseClassId);
        if (licenseClassRecord == null)
            throw new KeyNotFoundException($"licenseClass with id={oldLicenseRecord.LicenseClassId} does not exist.");

        var applicationTypeRecord = await ApplicationTypesData.FindByIdAsync((int)ApplicationTypeId.RenewDrivingLicense);
        if (applicationTypeRecord == null)
            throw new KeyNotFoundException($"applicationType with id={(int)ApplicationTypeId.RenewDrivingLicense} does not exist.");

        var personId = await DriverData.GetPersonIdByIdAsync(oldLicenseRecord.DriverId);

        var licenseClass = LicenseClass.Reconstitute(
                licenseClassRecord.Id,
                licenseClassRecord.Title,
                licenseClassRecord.Description,
                licenseClassRecord.MinAge,
                licenseClassRecord.ValidityLengthYears,
                Money.From(licenseClassRecord.Fees)
                );

        var application = Application.CreateRenewLocalLicense(
            personId,
            _currentUser.UserId,
            ApplicationType.Reconstitute(
                (ApplicationTypeId)applicationTypeRecord.Id,
                applicationTypeRecord.Title,
                Money.From(applicationTypeRecord.Fee)
            ),
            licenseClass);

        var applicationId = await ApplicationData.InsertAsync(
            new ApplicationRecord(
                application.PersonId,
                application.CreatedAt,
                (int)application.ApplicationTypeId,
                (byte)application.Status,
                application.LastStatusAt,
                application.PaidFees.Amount,
                application.CreatedByUserId
                ));

        if (applicationId == null)
            throw new InvalidOperationException("Failed to create application.");

        var newLicense = License.Issue(
            applicationId.Value,
            oldLicenseRecord.DriverId,
            licenseClass,
            notes,
            LicenseIssueReason.Renew,
            _currentUser.UserId
            );

        var oldLicense = License.Reconstitute(
            oldLicenseRecord.Id,
            oldLicenseRecord.ApplicationId,
            oldLicenseRecord.DriverId,
            oldLicenseRecord.LicenseClassId,
            oldLicenseRecord.IssueDate,
            oldLicenseRecord.ExpirationDate,
            oldLicenseRecord.Notes,
            Money.From(oldLicenseRecord.PaidFees),
            oldLicenseRecord.IsActive,
            (LicenseIssueReason)oldLicenseRecord.IssueReason,
            oldLicenseRecord.CreatedByUserId
            );

        oldLicense.DeActivate();

        var newLicenseId = await LicenseData.InsertAsync(
            new LicenseRecord(
                newLicense.Id,
                newLicense.ApplicationId,
                newLicense.DriverId,
                newLicense.LicenseClassId,
                newLicense.IssuedAt,
                newLicense.ExpiresAt,
                newLicense.Notes,
                newLicense.PaidFees.Amount,
                newLicense.IsActive,
                (int)newLicense.IssueReason,
                newLicense.CreatedByUserId
                )
            );

        await LicenseData.UpdateAsync(

            new LicenseRecord(
                oldLicense.Id,
                oldLicense.ApplicationId,
                oldLicense.DriverId,
                oldLicense.LicenseClassId,
                oldLicense.IssuedAt,
                oldLicense.ExpiresAt,
                oldLicense.Notes,
                oldLicense.PaidFees.Amount,
                oldLicense.IsActive,
                (int)oldLicense.IssueReason,
                oldLicense.CreatedByUserId
                )
            );

        return newLicenseId;
    }

    public async Task<int> ReplaceDamagedLocalLicenseAsync(int oldLicenseId, string? notes)
    {

        var oldLicenseRecord = await LicenseData.FindByIdAsync(oldLicenseId);

        if (oldLicenseRecord == null)
            throw new KeyNotFoundException($"License with id={oldLicenseId} does not exist.");

        if (!oldLicenseRecord.IsActive)
            throw new InvalidOperationException("Cannot replace inactive license.");

        if (oldLicenseRecord.ExpirationDate < DateTime.UtcNow)
            throw new InvalidOperationException("Cannot replace expired license.");


        var applicationTypeRecord = await ApplicationTypesData.FindByIdAsync((int)ApplicationTypeId.ReplacementDamaged);
        if (applicationTypeRecord == null)
            throw new KeyNotFoundException($"applicationType with id={(int)ApplicationTypeId.ReplacementDamaged} does not exist.");

        var personId = await DriverData.GetPersonIdByIdAsync(oldLicenseRecord.DriverId);

        var application = Application.CreateReplaceDamagedLocalLicense(
            personId,
            _currentUser.UserId,
            ApplicationType.Reconstitute(
                (ApplicationTypeId)applicationTypeRecord.Id,
                applicationTypeRecord.Title,
                Money.From(applicationTypeRecord.Fee)
            )
            );




        var applicationId = await ApplicationData.InsertAsync(
            new ApplicationRecord(
                application.PersonId,
                application.CreatedAt,
                (int)application.ApplicationTypeId,
                (byte)application.Status,
                application.LastStatusAt,
                application.PaidFees.Amount,
                application.CreatedByUserId
                ));

        if (applicationId == null)
            throw new InvalidOperationException("Failed to create application.");





        var newLicense = License.IssueDamagedReplacement(
            applicationId.Value,
            oldLicenseRecord.DriverId,
            oldLicenseRecord.LicenseClassId,
            oldLicenseRecord.ExpirationDate,
            notes,
            _currentUser.UserId
            );

        var oldLicense = License.Reconstitute(
            oldLicenseRecord.Id,
            oldLicenseRecord.ApplicationId,
            oldLicenseRecord.DriverId,
            oldLicenseRecord.LicenseClassId,
            oldLicenseRecord.IssueDate,
            oldLicenseRecord.ExpirationDate,
            oldLicenseRecord.Notes,
            Money.From(oldLicenseRecord.PaidFees),
            oldLicenseRecord.IsActive,
            (LicenseIssueReason)oldLicenseRecord.IssueReason,
            oldLicenseRecord.CreatedByUserId
            );

        oldLicense.DeActivate();

        var newLicenseId = await LicenseData.InsertAsync(
            new LicenseRecord(
                newLicense.Id,
                newLicense.ApplicationId,
                newLicense.DriverId,
                newLicense.LicenseClassId,
                newLicense.IssuedAt,
                newLicense.ExpiresAt,
                newLicense.Notes,
                newLicense.PaidFees.Amount,
                newLicense.IsActive,
                (int)newLicense.IssueReason,
                newLicense.CreatedByUserId
                )
            );

        await LicenseData.UpdateAsync(

            new LicenseRecord(
                oldLicense.Id,
                oldLicense.ApplicationId,
                oldLicense.DriverId,
                oldLicense.LicenseClassId,
                oldLicense.IssuedAt,
                oldLicense.ExpiresAt,
                oldLicense.Notes,
                oldLicense.PaidFees.Amount,
                oldLicense.IsActive,
                (int)oldLicense.IssueReason,
                oldLicense.CreatedByUserId
                )
            );

        return newLicenseId;
    }

    public async Task<int> ReplaceLostLocalLicenseAsync(int oldLicenseId, string? notes)
    {

        var oldLicenseRecord = await LicenseData.FindByIdAsync(oldLicenseId);

        if (oldLicenseRecord == null)
            throw new KeyNotFoundException($"License with id={oldLicenseId} does not exist.");

        if (!oldLicenseRecord.IsActive)
            throw new InvalidOperationException("Cannot replace inactive license.");

        if (oldLicenseRecord.ExpirationDate < DateTime.UtcNow)
            throw new InvalidOperationException("Cannot replace expired license.");


        var applicationTypeRecord = await ApplicationTypesData.FindByIdAsync((int)ApplicationTypeId.ReplacementLost);
        if (applicationTypeRecord == null)
            throw new KeyNotFoundException($"applicationType with id={(int)ApplicationTypeId.ReplacementLost} does not exist.");

        var personId = await DriverData.GetPersonIdByIdAsync(oldLicenseRecord.DriverId);

        var application = Application.CreateReplaceLostLocalLicense(
            personId,
            _currentUser.UserId,
            ApplicationType.Reconstitute(
                (ApplicationTypeId)applicationTypeRecord.Id,
                applicationTypeRecord.Title,
                Money.From(applicationTypeRecord.Fee)
            )
            );




        var applicationId = await ApplicationData.InsertAsync(
            new ApplicationRecord(
                application.PersonId,
                application.CreatedAt,
                (int)application.ApplicationTypeId,
                (byte)application.Status,
                application.LastStatusAt,
                application.PaidFees.Amount,
                application.CreatedByUserId
                ));

        if (applicationId == null)
            throw new InvalidOperationException("Failed to create application.");





        var newLicense = License.IssueLostReplacement(
            applicationId.Value,
            oldLicenseRecord.DriverId,
            oldLicenseRecord.LicenseClassId,
            oldLicenseRecord.ExpirationDate,
            notes,
            _currentUser.UserId
            );

        var oldLicense = License.Reconstitute(
            oldLicenseRecord.Id,
            oldLicenseRecord.ApplicationId,
            oldLicenseRecord.DriverId,
            oldLicenseRecord.LicenseClassId,
            oldLicenseRecord.IssueDate,
            oldLicenseRecord.ExpirationDate,
            oldLicenseRecord.Notes,
            Money.From(oldLicenseRecord.PaidFees),
            oldLicenseRecord.IsActive,
            (LicenseIssueReason)oldLicenseRecord.IssueReason,
            oldLicenseRecord.CreatedByUserId
            );

        oldLicense.DeActivate();

        var newLicenseId = await LicenseData.InsertAsync(
            new LicenseRecord(
                newLicense.Id,
                newLicense.ApplicationId,
                newLicense.DriverId,
                newLicense.LicenseClassId,
                newLicense.IssuedAt,
                newLicense.ExpiresAt,
                newLicense.Notes,
                newLicense.PaidFees.Amount,
                newLicense.IsActive,
                (int)newLicense.IssueReason,
                newLicense.CreatedByUserId
                )
            );

        await LicenseData.UpdateAsync(

            new LicenseRecord(
                oldLicense.Id,
                oldLicense.ApplicationId,
                oldLicense.DriverId,
                oldLicense.LicenseClassId,
                oldLicense.IssuedAt,
                oldLicense.ExpiresAt,
                oldLicense.Notes,
                oldLicense.PaidFees.Amount,
                oldLicense.IsActive,
                (int)oldLicense.IssueReason,
                oldLicense.CreatedByUserId
                )
            );

        return newLicenseId;
    }
}
