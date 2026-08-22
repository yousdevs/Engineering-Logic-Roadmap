namespace Data;

public sealed record TestAttemptRecord(

    int TestAppointmentId,
    int TestTypeId,
    bool? TestResult
    );

public sealed record TestAppointmentRecord(

    int? Id,
    int TestTypeId,
    int LocalDrivingLicenseApplicationId,
    DateTime AppointmentDate,
    decimal PaidFees,
    int CreatedByUserId,
    bool IsLocked,
    int? RetakeTestApplicationId
    );

public sealed record TestRecord(

    int? Id,
    int TestAppointmentId,
    bool TestResult,
    string? Notes,
    int CreatedByUserId
    );