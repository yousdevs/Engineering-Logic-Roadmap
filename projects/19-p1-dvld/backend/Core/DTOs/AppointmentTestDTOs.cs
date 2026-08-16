namespace Core.DTOs;

public sealed record ScheduleTestRequest(

    int TestTypeId,
    DateTime AppointmentDate
    );