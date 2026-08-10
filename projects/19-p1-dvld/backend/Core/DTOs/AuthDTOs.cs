namespace Core.DTOs;

public sealed record LoginRequest(string Username, string Password);
public sealed record AuthResult(string AccessToken, string RefreshToken);

public sealed record RotateRequest(string RefreshToken);

public sealed record ChangePasswordRequest
{

    public string CurrentPassword { get; }
    public string NewPassword { get; }

    public ChangePasswordRequest(string currentPassword, string newPassword)
    {
        if (string.IsNullOrWhiteSpace(NewPassword))
            throw new ArgumentException("New password cannot be empty.");

        if (NewPassword == CurrentPassword)
            throw new ArgumentException("New password must differ from current password.");

        CurrentPassword = currentPassword;
        NewPassword = newPassword;
    }
};