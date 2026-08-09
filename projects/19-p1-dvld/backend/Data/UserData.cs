using Microsoft.Data.SqlClient;

namespace Data;

public static class UserData
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
            throw new InvalidOperationException("UserData not initialized, call Initialize() first.");
        }
    }

    public static async Task<UserRecord?> GetByUsernameAsync(string username)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            SELECT 
                UserID,
                PersonID,
                UserName,
                Password,
                IsActive
            FROM Users
            WHERE UserName = @username;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@username", System.Data.SqlDbType.NVarChar).Value = username;

        await con.OpenAsync();
        await using var reader = await cmd.ExecuteReaderAsync();

        if (!await reader.ReadAsync())
            return null;

        return new UserRecord(
            (int)reader["UserID"],
            (int)reader["PersonID"],
            (string)reader["UserName"],
            (string)reader["Password"],
            (bool)reader["IsActive"]
            );
    }

    public static async Task<int?> InsertAsync(int personId, string username, string passwordHash, bool isActive)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            INSERT INTO Users(
            PersonID,
            UserName,
            Password,
            IsActive)
            VALUES(
            @personId,
            @username,
            @passwordHash,
            @isActive);
            SELECT CAST(SCOPE_IDENTITY() AS INT);
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@personId", System.Data.SqlDbType.Int).Value = personId;
        cmd.Parameters.Add("@username", System.Data.SqlDbType.NVarChar).Value = username;
        cmd.Parameters.Add("@passwordHash", System.Data.SqlDbType.NVarChar).Value = passwordHash;
        cmd.Parameters.Add("@isActive", System.Data.SqlDbType.Bit).Value = isActive;

        await con.OpenAsync();

        int? userId = (int?)await cmd.ExecuteScalarAsync();

        return userId;
    }

}
