namespace Core.DTOs;

public sealed record ScheduleTestRequest(

    int TestTypeId,
    DateTime AppointmentDate
    );

public sealed record TakeTestRequest(

    bool Passed,
    string? Notes
    );