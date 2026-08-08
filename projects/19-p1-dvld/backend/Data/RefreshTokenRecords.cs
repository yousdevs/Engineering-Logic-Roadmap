
namespace Data;

public sealed record RefreshTokenRecord(

        int RefreshTokenId,
        int UserId,
        DateTime ExpiresAt
        );
