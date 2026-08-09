namespace Core.DTOs;

public sealed record CreateUserForm(

    int PersonId,
    string Username,
    string Password
    );

