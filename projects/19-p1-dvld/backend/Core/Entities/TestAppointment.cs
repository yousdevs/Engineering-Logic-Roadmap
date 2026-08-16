namespace Core.Entities;

public sealed class TestAppointment
{
    public int Id { get; internal set; }

    public int TestTypeId { get; private set; }
    public int LocalDrivingLicenseAppId { get; private set; }
    public int CreatedByUserId { get; private set; }
    public int? RetakeTestAppId { get; private set; }
    public DateTime AppointmentDate { get; private set; }
    public bool IsLocked { get; private set; }
    public Money PaidFees { get; private set; }

    private TestAppointment(int id, int testTypeId, int localDrivingLicenseAppId, int createdByUserId, int? retakeTestAppId, DateTime appointmentDate, bool isLocked, Money paidFees)
    {

        Id = id;
        TestTypeId = testTypeId;
        LocalDrivingLicenseAppId = localDrivingLicenseAppId;
        CreatedByUserId = createdByUserId;
        RetakeTestAppId = retakeTestAppId;
        AppointmentDate = appointmentDate;
        IsLocked = isLocked;
        PaidFees = paidFees;
    }

    public static TestAppointment CreateNewAppointment(int localDrivingLicenseAppId, int createdByUserId, DateTime appointmentDate, TestType testType)
    {

        RequireAppointmentDateInFuture(appointmentDate);

        Money paidFees = testType.Fee;

        return new TestAppointment(-1, testType.Id, localDrivingLicenseAppId, createdByUserId, null, appointmentDate, false, paidFees);
    }

    public static TestAppointment CreateRetakeTestAppointment(int localDrivingLicenseAppId, int createdByUserId, int retakeTestAppId, DateTime appointmentDate, TestType testType)
    {

        RequireAppointmentDateInFuture(appointmentDate);

        Money paidFees = testType.Fee;

        return new TestAppointment(-1, testType.Id, localDrivingLicenseAppId, createdByUserId, retakeTestAppId, appointmentDate, false, paidFees);
    }

    public static TestAppointment Reconstitute(int id, int testTypeId, int localDrivingLicenseAppId,
        int createdByUserId, int? retakeTestAppId, DateTime appointmentDate, bool isLocked, Money paidFees)
    {

        return new TestAppointment(id, testTypeId, localDrivingLicenseAppId, createdByUserId, retakeTestAppId, appointmentDate, isLocked, paidFees);
    }
    public void Lock()
    {
        if (IsLocked)
            throw new InvalidOperationException("Appointment already locked.");

        IsLocked = true;
    }

    public void ChangeAppointmentDate(DateTime appointmentDate)
    {
        if (IsLocked)
            throw new InvalidOperationException("Cannot change appointment date for locked appointment.");

        RequireAppointmentDateInFuture(appointmentDate);

        AppointmentDate = appointmentDate;
    }

    private static void RequireAppointmentDateInFuture(DateTime appointmentDate)
    {

        if (appointmentDate < DateTime.UtcNow)
            throw new ArgumentException($"Appointment date must be in the future. recieved={appointmentDate}", nameof(appointmentDate));
    }
}
