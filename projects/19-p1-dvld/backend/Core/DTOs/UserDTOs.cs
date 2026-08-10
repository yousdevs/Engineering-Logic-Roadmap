namespace Core.DTOs;

public sealed record CreateUserForm(

    int PersonId,
    string Username,
    string Password
    );

public sealed record UserSummary(

    int UserId,
    string Firstname,
    string Lastname,
    string Username,
    string Status
    );

public sealed record ForceResetPasswordRequest(string NewPassword);
public sealed record UpdateUsernameRequest(string NewUsername);