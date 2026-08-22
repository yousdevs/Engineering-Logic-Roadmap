using Core.DTOs;
using Core.Entities;
using Data;

namespace Core.Services;

public sealed class ApplicationService
{

    private readonly ICurrentUser _currentUser;

    public ApplicationService(ICurrentUser currentUser)
    {
        _currentUser = currentUser;
    }

    public async Task<int> CreateAsync(NewApplicationRequest request)
    {
        return request.ApplicationTypeId switch
        {
            (int)ApplicationTypeId.NewLocalDrivingLicense =>
                await CreateNewLocalDrivingLicenseAsync(request),


            _ => throw new ArgumentException(
                $"Unsupported application type: {request.ApplicationTypeId}.",
                nameof(request))
        };
    }
    public async Task<int> CreateNewLocalDrivingLicenseAsync(NewApplicationRequest request)
    {

        var personDateOfBirth = await PersonData.FindDateOfBirthByIdAsync(request.PersonId);

        if (personDateOfBirth == null)
            throw new KeyNotFoundException($"Person with personId={request.PersonId} does not exist.");

        if (request.LicenseClassId == null)
            throw new ArgumentException(
                "LicenseClassId is required for a new local driving license application.",
                nameof(request.LicenseClassId));

        var licenseClassRecord = await LicenseClassData.FindByIdAsync(request.LicenseClassId.Value);

        if (licenseClassRecord == null)
            throw new KeyNotFoundException($"LicenseClass with licenseClassId={request.LicenseClassId} does not exist.");


        var activeOrCompletedApplicationExists = await ApplicationData.ExistsNewOrCompletedByPersonIdAndApplicationTypeIdAndLicenseClassIdAsync(request.PersonId, (int)ApplicationTypeId.NewLocalDrivingLicense, request.LicenseClassId.Value);

        if (activeOrCompletedApplicationExists)
            throw new InvalidOperationException("Person already has active or completed application for this license class.");


        var applicationTypeRecord = await ApplicationTypesData.FindByIdAsync((int)ApplicationTypeId.NewLocalDrivingLicense);

        if (applicationTypeRecord == null)
            throw new KeyNotFoundException($"ApplicationType with ApplicationTypeId={(int)ApplicationTypeId.NewLocalDrivingLicense} does not exists.");

        var application = Application.CreateNewLocalDrivingLicense(
            request.PersonId,
            personDateOfBirth.Value,
            ApplicationType.Reconstitute(
                (ApplicationTypeId)applicationTypeRecord.Id,
                applicationTypeRecord.Title,
                Money.From(applicationTypeRecord.Fee)
            ), LicenseClass.Reconstitute(
                licenseClassRecord.Id,
                licenseClassRecord.Title,
                licenseClassRecord.Description,
                licenseClassRecord.MinAge,
                licenseClassRecord.ValidityLengthYears,
                Money.From(licenseClassRecord.Fees)), _currentUser.UserId);

        int? applicationId = await ApplicationData.InsertAsync(new ApplicationRecord(
            application.PersonId,
            application.CreatedAt,
            (int)application.ApplicationTypeId,
            (byte)application.Status,
            application.LastStatusAt,
            application.PaidFees.Amount,
            application.CreatedByUserId
            ));

        if (applicationId == null)
            throw new InvalidOperationException();

        await LocalDrivingLicenseApplicationData.InsertAsync(applicationId.Value, request.LicenseClassId.Value);

        return applicationId.Value;
    }

}
