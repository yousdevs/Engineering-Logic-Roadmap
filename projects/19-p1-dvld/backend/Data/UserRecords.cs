namespace Data;

public sealed record UserRecord(
    int UserID,
    int PersonID,
    string UserName,
    string PasswordHash,
    bool IsActive
    );

public sealed record UserSummaryRecord(

    int UserId,
    string FirstName,
    string LastName,
    string Username,
    bool IsActive
    );

public sealed record UserPage(

    IReadOnlyList<UserSummaryRecord> Items,
    int Total
    );

public sealed record UserDetailsRecord(
    int UserId,
    int PersonId,
    string UserName,
    string FirstName,
    string SecondName,
    string? ThirdName,
    string LastName,
    bool IsActive
    );