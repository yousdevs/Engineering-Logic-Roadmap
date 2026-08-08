namespace Data;

public sealed record UserRecord(
    int UserID,
    int PersonID,
    string UserName,
    string PasswordHash,
    bool IsActive
    );
