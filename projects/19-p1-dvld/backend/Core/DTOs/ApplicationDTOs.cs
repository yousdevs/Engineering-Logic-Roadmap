namespace Core.DTOs;


public sealed record NewApplicationRequest(
    int ApplicationTypeId,
    int PersonId,
    int? LicenseClassId
    );