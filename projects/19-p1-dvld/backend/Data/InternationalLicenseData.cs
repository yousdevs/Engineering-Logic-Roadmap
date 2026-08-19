
using Microsoft.Data.SqlClient;

namespace Data;

public sealed record InternationalLicenseRecord(

    int ApplicationId,
    int DriverId,
    int IssuedUsingLocalLicenseId,
    DateTime IssueDate,
    DateTime ExpirationDate,
    bool IsActive,
    int CreatedByUserId
    );

public static class InternationalLicenseData
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
            throw new InvalidOperationException("InternationalLicenseData not initialized, call Initialize() first.");
        }
    }

    public static async Task<int> InsertAsync(InternationalLicenseRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """

            INSERT INTO InternationalLicenses (
                ApplicationID,
                DriverID,
                IssuedUsingLocalLicenseID,
                IssueDate,
                ExpirationDate,
                IsActive,
                CreatedByUserID
               )
            VALUES(
                @applicationId,
                @driverId,
                @issuedUsingLocalLicenseId,
                @issueDate,
                @expirationDate,
                @isActive,
                @createdByUserId
            );

            SELECT CAST(SCOPE_IDENTITY() AS INT);
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@applicationId", System.Data.SqlDbType.Int).Value = record.ApplicationId;
        cmd.Parameters.Add("@driverId", System.Data.SqlDbType.Int).Value = record.DriverId;
        cmd.Parameters.Add("@issuedUsingLocalLicenseId", System.Data.SqlDbType.Int).Value = record.IssuedUsingLocalLicenseId;
        cmd.Parameters.Add("@issueDate", System.Data.SqlDbType.DateTime).Value = record.IssueDate;
        cmd.Parameters.Add("@expirationDate", System.Data.SqlDbType.DateTime).Value = record.ExpirationDate;
        cmd.Parameters.Add("@isActive", System.Data.SqlDbType.Bit).Value = record.IsActive;
        cmd.Parameters.Add("@createdByUserId", System.Data.SqlDbType.Int).Value = record.CreatedByUserId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        return Convert.ToInt32(result);
    }

    public static async Task<bool> ExistActiveByDriverId(int driverId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """

            SELECT CASE WHEN EXISTS(
                SELECT 1
                FROM InternationalLicenses
                WHERE DriverID = @driverId
            )
            THEN CAST(1 AS BIT) 
            ELSE CAST(0 AS BIT)
            END;
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@driverId", System.Data.SqlDbType.Int).Value = driverId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        return Convert.ToBoolean(result);
    }
}
