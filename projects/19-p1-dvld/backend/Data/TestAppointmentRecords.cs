namespace Data;

public sealed record TestAttemptRecord(

    int TestAppointmentId,
    int TestTypeId,
    bool? TestResult
    );

public sealed record TestAppointmentRecord(

    int TestTypeId,
    int LocalDrivingLicenseApplicationId,
    DateTime AppointmentDate,
    decimal PaidFees,
    int CreatedByUserId,
    bool IsLocked,
    int? RetakeTestApplicationId
    );