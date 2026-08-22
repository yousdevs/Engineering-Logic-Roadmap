namespace Core;


public enum TestTypeId
{
    Vision = 1,
    Written = 2,
    Practical = 3
}

public enum TestOutcome
{
    Failed = 0,
    Passed = 1
}

public enum TestStepStatus
{
    Locked, // Prerequisite test has not passed.
    ReadyToSchedule, // This test is the next permitted test, but no appointment exists.
    Scheduled, // An appointment exists, but the test has not been taken.
    Passed, // Latest attempt passed.
    RetakeRequired // Latest attempt failed and must be retaken.
}

public enum TestStepAction
{
    None, // Locked and Passed
    ScheduleTest, // map to ReadyToSchedule
    TakeTest, // map to Scheduled
    ScheduleRetakeTest // RetakeRequired
}

public sealed record TestAttempt(

    int TestAppointmentId,
    TestTypeId TestTypeId,
    TestOutcome? Outcome
    );
// TestOutcome? :
// - null -> scheduled
// - Passed -> Taken and passed
// - Failed -> Taken and failed.

public sealed record TestWorkflowStep(

    TestTypeId TestTypeId,
    int Order,
    TestStepStatus Status,
    TestStepAction Action,
    int? TestAppointmentId
    );


public sealed class LocalDrivingLicenseTestWorkflow
{
    public IReadOnlyList<TestWorkflowStep> Steps { get; }

    public TestWorkflowStep? CurrentStep { get; }

    public bool CanIssueLicense { get; }

    private static readonly TestTypeId[] TestOrder =
        [
            TestTypeId.Vision,
            TestTypeId.Written,
            TestTypeId.Practical
        ];

    private LocalDrivingLicenseTestWorkflow(

        IReadOnlyList<TestWorkflowStep> steps,
        TestWorkflowStep? currentStep,
        bool canIssueLicense
        )
    {

        Steps = steps;
        CurrentStep = currentStep;
        CanIssueLicense = canIssueLicense;
    }

    public static LocalDrivingLicenseTestWorkflow FromAttempts(IReadOnlyCollection<TestAttempt> attempts)
    {
        ArgumentNullException.ThrowIfNull(attempts);

        ValidateAttempts(attempts);

        var latestAttempts = GetLatestAttempts(attempts);

        var steps = new List<TestWorkflowStep>(TestOrder.Length);

        bool previousTestPassed = true;

        for (int i = 0; i < TestOrder.Length; i++)
        {

            TestTypeId testTypeId = TestOrder[i];

            int order = i + 1;

            latestAttempts.TryGetValue(testTypeId, out TestAttempt? attempt);

            TestWorkflowStep step;

            if (!previousTestPassed)
            {
                step = new TestWorkflowStep(

                    testTypeId,
                    order,
                    TestStepStatus.Locked,
                    TestStepAction.None,
                    attempt?.TestAppointmentId
                    );
            }
            else
            {
                step = DetermineStep(testTypeId, order, attempt);
            }

            steps.Add(step);

            previousTestPassed = step.Status == TestStepStatus.Passed;
        }

        bool canIssueLicense = steps.All(step => step.Status == TestStepStatus.Passed);

        TestWorkflowStep? currentStep = canIssueLicense ? null : steps.First(step => step.Status != TestStepStatus.Passed);

        return new LocalDrivingLicenseTestWorkflow(steps, currentStep, canIssueLicense);
    }

    private static TestWorkflowStep DetermineStep(TestTypeId testTypeId, int order, TestAttempt? attempt)
    {

        if (attempt is null)
        {
            return new TestWorkflowStep(
                testTypeId,
                order,
                TestStepStatus.ReadyToSchedule,
                TestStepAction.ScheduleTest,
                null
                );
        }

        return attempt.Outcome switch
        {

            null => new TestWorkflowStep(
                testTypeId,
                order,
                TestStepStatus.Scheduled,
                TestStepAction.TakeTest,
                attempt.TestAppointmentId
                ),

            TestOutcome.Passed => new TestWorkflowStep(
                testTypeId,
                order,
                TestStepStatus.Passed,
                TestStepAction.None,
                attempt.TestAppointmentId
                ),

            TestOutcome.Failed => new TestWorkflowStep(
                testTypeId,
                order,
                TestStepStatus.RetakeRequired,
                TestStepAction.ScheduleRetakeTest,
                attempt.TestAppointmentId
                ),

            _ => throw new InvalidOperationException(

                    $"Unsupported test outcome for test type {testTypeId}."
                )
        };
    }

    private static Dictionary<TestTypeId, TestAttempt> GetLatestAttempts(IReadOnlyCollection<TestAttempt> attempts)
    {
        return attempts
            .GroupBy(attempt => attempt.TestTypeId)
            .ToDictionary(

                group => group.Key,
                group => group
                .OrderByDescending(attempt => attempt.TestAppointmentId) // larger appointment id = newer appointment
                .First()
            );
    }

    private static void ValidateAttempts(IReadOnlyCollection<TestAttempt> attempts)
    {

        foreach (TestAttempt attempt in attempts)
        {
            if (attempt.TestAppointmentId <= 0)
            {
                throw new ArgumentException(
                    $"TestAppointmentId must be greater than zero. " +
                    $"Recieved {attempt.TestAppointmentId}.",
                    nameof(attempts)
                    );
            }

            if (!Enum.IsDefined(attempt.TestTypeId))
            {
                throw new ArgumentException(
                    $"Unknown TestTypeId: ${(int)attempt.TestTypeId}.",
                    nameof(attempts)
                    );
            }

            if (attempt.Outcome is not null && !Enum.IsDefined(attempt.Outcome.Value))
            {
                throw new ArgumentException(
                    $"Unknown TestOutcome: {(int)attempt.Outcome.Value}.",
                    nameof(attempts)
                    );
            }
        }
    }
}
