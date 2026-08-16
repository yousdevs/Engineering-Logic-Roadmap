
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

    public async Task ScheduleRetakeTest(int applicationid, int testTypeId, DateTime appointmentDate)
    {

        // is no testtypeid with passed ?
        // is there testtypeid with failed?
        // is no appointment linked to application?
    }
}
