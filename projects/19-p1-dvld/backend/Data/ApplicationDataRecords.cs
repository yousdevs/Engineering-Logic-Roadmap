namespace Data;


public sealed record ApplicationRecord(

    int ApplicantPersonId,
    DateTime ApplicationDate,
    int ApplicationTypeId,
    byte ApplicationStatus,
    DateTime LastStatusDate,
    decimal PaidFees,
    int CreatedByUserId
    );