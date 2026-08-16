
using Core.Entities;
using Data;

namespace Core.Services;

public sealed class TestService
{
    private readonly ICurrentUser _currentUser;

    public TestService(ICurrentUser currentUser)
    {
        _currentUser = currentUser;
    }

    public async Task<int> ScheduleTestAsync(int applicationId, int testTypeId, DateTime appointmentDate)
    {

        var applicationStatus = await ApplicationData.GetApplicationStatus(applicationId);

        if (applicationStatus == null)
            throw new KeyNotFoundException($"Application with id={applicationId} does not exists.");

        if ((ApplicationStatus)applicationStatus != ApplicationStatus.New)
            throw new InvalidOperationException("Application must be New.");

        int? localDrivingLicenseAppId = await LocalDrivingLicenseApplicationData.GetIdByApplicationId(applicationId);

        if (localDrivingLicenseAppId == null)
            throw new InvalidOperationException("This application is not local driving license application.");

        var historyRecords = await TestAppointmentData.GetHistoryAsync(localDrivingLicenseAppId.Value);

        var attempts = historyRecords.Select(x =>
            new TestAttempt(
                x.TestAppointmentId,
                (TestTypeId)x.TestTypeId,
                x.TestResult.HasValue ? x.TestResult.Value ? TestOutcome.Passed : TestOutcome.Failed : null
        )).ToList();

        var workflow = LocalDrivingLicenseTestWorkflow.FromAttempts(attempts);

        if (workflow.CurrentStep == null)
            throw new InvalidOperationException($"Cannot Schedule Test, allready passed all tests.");

        if (workflow.CurrentStep.TestTypeId != (TestTypeId)testTypeId)
            throw new InvalidOperationException($"Cannot schedule test with testTypeId={testTypeId}, schedule for {workflow.CurrentStep.TestTypeId} instead.");

        if (workflow.CurrentStep.Action != TestStepAction.ScheduleTest)
            throw new InvalidOperationException($"Cannot schedule this test. The required action is TakeTest.");

        var testType = await TestTypeData.FindByIdAsync(testTypeId);
        if (testType == null)
            throw new KeyNotFoundException("TestType does not exist.");

        var appointment = TestAppointment.CreateNewAppointment(
            localDrivingLicenseAppId.Value,
            _currentUser.UserId,
            appointmentDate,
            TestType.Reconstitute(testType.Id, testType.Title, testType.Description, Money.From(testType.Fee)));

        var appintmentId = await TestAppointmentData.InsertAppointmentAsync(

            new TestAppointmentRecord(
                appointment.Id,
                appointment.TestTypeId,
                appointment.LocalDrivingLicenseAppId,
                appointment.AppointmentDate,
                appointment.PaidFees.Amount,
                appointment.CreatedByUserId,
                appointment.IsLocked,
                appointment.RetakeTestAppId
                )
                );

        if (appintmentId == null)
            throw new OperationCanceledException("Failed to recieve appointment id from the insert appointment operation.");

        return (int)appintmentId;

    }

    public async Task<int> TakeTestAsync(int appointmentId, bool passed, string? notes)
    {

        var appointmentRecord = await TestAppointmentData.FindAppointmentByIdAsync(appointmentId);

        if (appointmentRecord == null || appointmentRecord.Id == null)
            throw new KeyNotFoundException($"Appointment with id={appointmentId} does not exist.");

        var status = await LocalDrivingLicenseApplicationData.GetApplicationStatusByIdAsync(appointmentRecord.LocalDrivingLicenseApplicationId);

        if (status == null)
            throw new KeyNotFoundException($"Cannot find application with id={appointmentRecord.LocalDrivingLicenseApplicationId}.");

        if ((ApplicationStatus)status != ApplicationStatus.New)
            throw new InvalidOperationException("Cannot Take test for completed or cancelled applications.");


        var historyRecords = await TestAppointmentData.GetHistoryAsync(appointmentRecord.LocalDrivingLicenseApplicationId);

        var attempts = historyRecords.Select(x =>
            new TestAttempt(
                x.TestAppointmentId,
                (TestTypeId)x.TestTypeId,
                x.TestResult.HasValue ? x.TestResult.Value ? TestOutcome.Passed : TestOutcome.Failed : null
        )).ToList();

        var workflow = LocalDrivingLicenseTestWorkflow.FromAttempts(attempts);

        if (workflow.CurrentStep == null)
            throw new InvalidOperationException("Allready passed all tests.");

        if (workflow.CurrentStep.TestTypeId != (TestTypeId)appointmentRecord.TestTypeId)
            throw new InvalidOperationException($"Cannot take this test, take {workflow.CurrentStep.TestTypeId} instead.");

        if (workflow.CurrentStep.TestAppointmentId != appointmentRecord.Id)
            throw new InvalidOperationException(
                $"Appointment {appointmentRecord.Id} is not the currently scheduled appointment.");

        if (workflow.CurrentStep.Action != TestStepAction.TakeTest)
            throw new InvalidOperationException($"Cannot take test, the required action is {workflow.CurrentStep.Action}.");

        var appointment = TestAppointment.Reconstitute(
            appointmentRecord.Id.Value,
            appointmentRecord.TestTypeId,
            appointmentRecord.LocalDrivingLicenseApplicationId,
            appointmentRecord.CreatedByUserId,
            appointmentRecord.RetakeTestApplicationId,
            appointmentRecord.AppointmentDate,
            appointmentRecord.IsLocked,
            Money.From(appointmentRecord.PaidFees)
            );

        appointment.Lock();

        int? testId = await TestAppointmentData.InsertTestAsync(

            new TestRecord(null, appointment.Id, passed, notes, _currentUser.UserId)
            );

        if (testId == null)
            throw new OperationCanceledException("Failed to save test.");

        await TestAppointmentData.UpdateTestAppointmentAsync(

            new TestAppointmentRecord(
                appointment.Id,
                appointment.TestTypeId,
                appointment.LocalDrivingLicenseAppId,
                appointment.AppointmentDate,
                appointment.PaidFees.Amount,
                appointment.CreatedByUserId,
                appointment.IsLocked,
                appointment.RetakeTestAppId
                )
            );

        return testId.Value;
    }
    public async Task ScheduleRetakeTest(int applicationid, int testTypeId, DateTime appointmentDate)
    {

        // is no testtypeid with passed ?
        // is there testtypeid with failed?
        // is no appointment linked to application?
    }
}
