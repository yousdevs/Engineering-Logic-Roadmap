using Microsoft.Data.SqlClient;

namespace Data;

public static class RefreshTokenData
{

    private static string _connectionString = null!;

    public static void Initialize(string connectionString)
    {
        _connectionString = connectionString;
    }

    private static void RequireInitialized()
    {
        if (_connectionString is null)
        {
            throw new InvalidOperationException("RefreshTokenData not initialized, call Initialize() first.");
        }
    }

    // login
    public static async Task CreateAsync(int userId, string tokenHash, DateTime expiresAt)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            INSERT INTO RefreshTokens(
            UserId,
            TokenHash,
            ExpiresAt
            )
            VALUES(
            @userId,
            @tokenHash,
            @expiresAt
            );
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@userId", System.Data.SqlDbType.Int).Value = userId;
        cmd.Parameters.Add("@tokenHash", System.Data.SqlDbType.NVarChar).Value = tokenHash;
        cmd.Parameters.Add("@expiresAt", System.Data.SqlDbType.DateTime).Value = expiresAt;

        await con.OpenAsync();

        await cmd.ExecuteNonQueryAsync();

    }



    // refresh endpoint - find and validate token
    public static async Task<RefreshTokenRecord?> GetActiveByHashAsync(string tokenHash)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT RefreshTokenId,
                   UserId,
                   ExpiresAt
            FROM RefreshTokens
            WHERE TokenHash = @tokenHash
            AND RevokedAt IS NULL
            AND ExpiresAt > GETUTCDATE();
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@tokenHash", System.Data.SqlDbType.NVarChar).Value = tokenHash;

        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        if (!await reader.ReadAsync())
            return null;

        return new RefreshTokenRecord(
            (int)reader["RefreshTokenId"],
            (int)reader["UserId"],
            (DateTime)reader["ExpiresAt"]
            );
    }


    // refresh endpoint - revoke old token after rotation
    public static async Task<bool> RevokeAsync(int refreshTokenId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            UPDATE RefreshTokens
            SET RevokedAt = GETUTCDATE()
            WHERE RefreshTokenId = @refreshTokenId;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@refreshTokenId", System.Data.SqlDbType.Int).Value = refreshTokenId;

        await con.OpenAsync();

        int affected = await cmd.ExecuteNonQueryAsync();

        return affected == 1;
    }

    // logout - revoke all user tokens
    public static async Task RevokeAllByUserIdAsync(int userId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            UPDATE RefreshTokens
            SET RevokedAt = GETUTCDATE()
            WHERE UserId = @userId;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@userId", System.Data.SqlDbType.Int).Value = userId;

        await con.OpenAsync();

        await cmd.ExecuteNonQueryAsync();
    }

}
