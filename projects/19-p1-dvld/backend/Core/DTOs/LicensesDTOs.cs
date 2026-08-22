
namespace Core.DTOs;

public sealed record IssueLocalDrivingLicenseRequest(

    int ApplicationId,
    string? Notes
    );

public sealed record IssueInternationalLicenseRequest(
    int LocalLicenseId
    );

public sealed record RenewLocalLicenseRequest
(
    string? Notes
);

public sealed record ReplaceDamagedLicenseRequest(

    string? Notes
    );

public sealed record ReplaceLostLicenseRequest(

    string? Notes
    );