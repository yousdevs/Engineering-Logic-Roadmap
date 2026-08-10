
namespace Data;

public sealed record RefreshTokenRecord(

        int RefreshTokenId,
        int UserId,
        string Username,
        bool IsActive,
        DateTime ExpiresAt
        );
