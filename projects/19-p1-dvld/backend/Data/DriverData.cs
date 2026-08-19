using Microsoft.Data.SqlClient;

namespace Data;

public sealed record DriverRecord(

    int PersonId,
    int CreatedByUserId,
    DateTime CreatedDate
    );
public static class DriverData
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
            throw new InvalidOperationException("DriverData not initialized, call Initialize() first.");
        }
    }

    public static async Task<bool> ExistsByPersonIdAsync(int personId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);
        const string query = """
            SELECT CASE WHEN EXISTS(
                SELECT 1 FROM Drivers
                WHERE PersonID = @personId
                )
            THEN CAST(1 AS BIT) ELSE CAST(0 AS BIT) END;
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@personId", System.Data.SqlDbType.Int).Value = personId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        return Convert.ToBoolean(result);
    }

    public static async Task<int> InsertAsync(DriverRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);
        const string query = """

            INSERT INTO Drivers(
                PersonID,
                CreatedByUserID,
                CreatedDate)
            VALUES(
                @personId,
                @createdByUserId,
                @createdDate
            );
            SELECT CAST(SCOPE_IDENTITY() AS INT);
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@personId", System.Data.SqlDbType.Int).Value = record.PersonId;
        cmd.Parameters.Add("@createdByUserId", System.Data.SqlDbType.Int).Value = record.CreatedByUserId;
        cmd.Parameters.Add("@createdDate", System.Data.SqlDbType.DateTime).Value = record.CreatedDate;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        return Convert.ToInt32(result);
    }

    public static async Task<int?> GetIdByPersonIdAsync(int personId)
    {
        RequireInitialized();
        await using var con = new SqlConnection(_connectionString);

        const string query = """
            SELECT DriverID
            FROM Drivers
            WHERE PersonID = @personId;
            """;
        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@personId", System.Data.SqlDbType.Int).Value = personId;
        await con.OpenAsync();

        return (int?)await cmd.ExecuteScalarAsync();
    }
}
