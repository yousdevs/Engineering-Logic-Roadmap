namespace Data;


public sealed record LicenseClassRecord(

    int Id,
    string Title,
    string Description,
    int MinAge,
    int ValidityLengthYears,
    decimal Fees
    );
