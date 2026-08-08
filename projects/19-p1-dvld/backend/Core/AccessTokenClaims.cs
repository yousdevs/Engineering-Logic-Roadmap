namespace Core;


public sealed record AccessTokenClaims(

    int UserId,
    string Username,
    bool IsActive
    );
