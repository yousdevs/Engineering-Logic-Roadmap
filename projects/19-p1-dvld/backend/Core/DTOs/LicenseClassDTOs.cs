namespace Core.DTOs;

public sealed record LicenseClassSummary(

    int Id,
    string Title,
    string Description,
    int MinAge,
    int ValidityYears,
    decimal Fees
    );
