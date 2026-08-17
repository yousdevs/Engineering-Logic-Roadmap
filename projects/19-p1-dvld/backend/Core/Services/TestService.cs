
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
    public async Task<int> ScheduleRetakeTestAsync(int applicationId, DateTime appointmentDate)
    {

        var applicationStatus = await ApplicationData.GetApplicationStatus(applicationId);

        if (applicationStatus == null)
            throw new KeyNotFoundException($"Application with id={applicationId} does not exist.");

        if ((ApplicationStatus)applicationStatus != ApplicationStatus.New)
            throw new InvalidOperationException("Application must be New.");

        var localDrivingLicenseApplicationId = await LocalDrivingLicenseApplicationData.GetIdByApplicationId(applicationId);

        if (localDrivingLicenseApplicationId == null)
            throw new InvalidOperationException("This application is not local driving license application.");

        var historyRecords = await TestAppointmentData.GetHistoryAsync(localDrivingLicenseApplicationId.Value);

        var attempts = historyRecords.Select(x =>
            new TestAttempt(
                x.TestAppointmentId,
                (TestTypeId)x.TestTypeId,
                x.TestResult.HasValue ? x.TestResult.Value ? TestOutcome.Passed : TestOutcome.Failed : null
        )).ToList();

        var workflow = LocalDrivingLicenseTestWorkflow.FromAttempts(attempts);

        if (workflow.CurrentStep == null)
            throw new InvalidOperationException("All Tests passed.");

        if (workflow.CurrentStep.Action != TestStepAction.ScheduleRetakeTest)
            throw new InvalidOperationException($"Invalid action, use {workflow.CurrentStep.Action} instead.");

        var personId = await ApplicationData.GetPersonIdByApplicationIdAsync(applicationId);
        if (personId == null)
            throw new KeyNotFoundException($"Application with id={applicationId} does not exist.");

        var applicationTypeRecord = await ApplicationTypesData.FindByIdAsync((int)ApplicationTypeId.RetakeTest);
        if (applicationTypeRecord == null)
            throw new KeyNotFoundException($"ApplicationType with id={(int)ApplicationTypeId.RetakeTest} does not exist.");


        var testTypeRecord = await TestTypeData.FindByIdAsync((int)workflow.CurrentStep.TestTypeId);
        if (testTypeRecord == null)
            throw new KeyNotFoundException($"TestType with id={(int)workflow.CurrentStep.TestTypeId} does not exist");

        var retakeApplication = Application.CreateRetakeTest(
            personId.Value,
            _currentUser.UserId,
            ApplicationType.Reconstitute((ApplicationTypeId)applicationTypeRecord.Id, applicationTypeRecord.Title, Money.From(applicationTypeRecord.Fee)));

        var retakeApplicationId = await ApplicationData.InsertAsync(
            new ApplicationRecord(
                retakeApplication.PersonId,
                retakeApplication.CreatedAt,
                (int)retakeApplication.ApplicationTypeId,
                (byte)retakeApplication.Status,
                retakeApplication.LastStatusAt,
                retakeApplication.PaidFees.Amount,
                retakeApplication.CreatedByUserId)
            );

        if (retakeApplicationId == null)
            throw new InvalidOperationException("Failed to insert RetakeApplication.");



        var appointment = TestAppointment.CreateRetakeTestAppointment(
            localDrivingLicenseApplicationId.Value,
            _currentUser.UserId,
            retakeApplicationId.Value,
            appointmentDate,
            TestType.Reconstitute(testTypeRecord.Id, testTypeRecord.Title, testTypeRecord.Description, Money.From(testTypeRecord.Fee)));

        var appointmentId = await TestAppointmentData.InsertAppointmentAsync(

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

        if (appointmentId == null)
            throw new InvalidOperationException("Failed to insert Appointment.");

        return appointmentId.Value;
    }


}
