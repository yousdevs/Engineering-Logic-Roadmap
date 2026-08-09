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


    public static async Task<UserPage> FindAllAsync(int offset, int limit)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            SELECT 
                u.UserID,
                u.UserName,
                u.IsActive,
                p.FirstName,
                p.LastName,
                COUNT(*) OVER() AS Total
            FROM Users u
            INNER JOIN People p
            ON u.PersonID = p.PersonID 
            ORDER BY FirstName, u.UserID
            OFFSET @offset ROWS
            FETCH NEXT @limit ROWS ONLY;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@offset", System.Data.SqlDbType.Int).Value = offset;
        cmd.Parameters.Add("@limit", System.Data.SqlDbType.Int).Value = limit;

        await con.OpenAsync();
        await using var reader = await cmd.ExecuteReaderAsync();

        var items = new List<UserSummaryRecord>();
        int total = 0;

        while (await reader.ReadAsync())
        {
            if (items.Count == 0)
                total = (int)reader["Total"];

            items.Add(new UserSummaryRecord(
                (int)reader["UserID"],
                (string)reader["FirstName"],
                (string)reader["LastName"],
                (string)reader["UserName"],
                (bool)reader["IsActive"]
                ));
        }

        return new UserPage(items, total);

    }
}
