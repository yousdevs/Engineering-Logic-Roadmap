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

    public static async Task<UserRecord?> FindByIdAsync(int userId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT UserID,
                   PersonID,
                   UserName,
                   Password,
                   IsActive
            FROM Users
            WHERE UserID = @userId;
         ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@userId", System.Data.SqlDbType.Int).Value = userId;

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

    public static async Task<bool> UpdateAsync(UserRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            UPDATE Users
            SET 
                PersonID = @personId,
                UserName = @username,
                Password = @passwordHash,
                IsActive = @isActive
            WHERE UserID = @userId;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@userId", System.Data.SqlDbType.Int).Value = record.UserID;
        cmd.Parameters.Add("@personId", System.Data.SqlDbType.Int).Value = record.PersonID;
        cmd.Parameters.Add("@username", System.Data.SqlDbType.NVarChar).Value = record.UserName;
        cmd.Parameters.Add("@passwordHash", System.Data.SqlDbType.NVarChar).Value = record.PasswordHash;
        cmd.Parameters.Add("@isActive", System.Data.SqlDbType.Bit).Value = record.IsActive;

        await con.OpenAsync();

        int affected = await cmd.ExecuteNonQueryAsync();

        return affected > 0;
    }

    public static async Task<bool> ExistsByUserId(int userId)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            SELECT CASE WHEN EXISTS (SELECT 1 FROM Users WHERE UserID = @userId) THEN 1 ELSE 0 END;
        ";

        await using var cmd = new SqlCommand(query, con);

        cmd.Parameters.Add("@userId", System.Data.SqlDbType.Int).Value = userId;

        await con.OpenAsync();

        return (int)(await cmd.ExecuteScalarAsync())! == 1;
    }


    public static async Task<UserDetailsRecord?> GetDetailsByIdAsync(int userId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
        
            SELECT 
                u.PersonID,
                u.UserName,
                u.IsActive,
                p.FirstName,
                p.SecondName,
                p.ThirdName,
                p.LastName
            FROM Users u
            INNER JOIN People p
            ON u.PersonID = p.PersonID
            WHERE u.UserID = @userId;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@userId", System.Data.SqlDbType.Int).Value = userId;

        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        if (!await reader.ReadAsync())
            return null;

        return new UserDetailsRecord(
            userId,
            (int)reader["PersonID"],
            (string)reader["UserName"],
            (string)reader["FirstName"],
            (string)reader["SecondName"],
            reader.IsDBNull(reader.GetOrdinal("ThirdName")) ? null : (string)reader["ThirdName"],
            (string)reader["LastName"],
            (bool)reader["IsActive"]
            );
    }
}
