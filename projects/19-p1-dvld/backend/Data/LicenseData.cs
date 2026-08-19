using Microsoft.Data.SqlClient;

namespace Data;


public sealed record LicenseRecord(

    int ApplicationId,
    int DriverId,
    int LicenseClassId,
    DateTime IssueDate,
    DateTime ExpirationDate,
    string? Notes,
    decimal PaidFees,
    bool IsActive,
    int IssueReason,
    int CreatedByUserId
    );

public static class LicenseData
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
            throw new InvalidOperationException("LicenseData not initialized, call Initialize() first.");
        }
    }

    public static async Task<bool> ExistsWithSameLicenseClassByPersonId(int personId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);
        const string query = """

            SELECT CASE WHEN EXISTS (
             SELECT 1 FROM Licenses l 
             INNER JOIN Drivers d
             ON l.DriverID = d.DriverID
             INNER JOIN LocalDrivingLicenseApplications loc
             ON l.ApplicationID = loc.ApplicationID
             WHERE d.PersonID = @personId
             AND l.LicenseClass = loc.LicenseClassID
             ) THEN CAST(1 AS BIT) ELSE CAST(0 AS BIT) END;

            """;
        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@personId", System.Data.SqlDbType.Int).Value = personId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();
        return Convert.ToBoolean(result);

    }


    public static async Task<int> InsertAsync(LicenseRecord record)
    {
        RequireInitialized();
        await using var con = new SqlConnection(_connectionString);

        const string query = """

            INSERT INTO Licenses(
                ApplicationID,
                DriverID,
                LicenseClass,
                IssueDate,
                ExpirationDate,
                Notes,
                PaidFees,
                IsActive,
                IssueReason,
                CreatedByUserID
                )
            VALUES(
                @applicationId,
                @driverId,
                @licenseClassId,
                @issueDate,
                @expirationDate,
                @notes,
                @paidFees,
                @isActive,
                @issueReason,
                @createdByUserId
                );

            SELECT CAST(SCOPE_IDENTITY() AS INT);
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@applicationId", System.Data.SqlDbType.Int).Value = record.ApplicationId;
        cmd.Parameters.Add("@driverId", System.Data.SqlDbType.Int).Value = record.DriverId;
        cmd.Parameters.Add("@licenseClassId", System.Data.SqlDbType.Int).Value = record.LicenseClassId;
        cmd.Parameters.Add("@issueDate", System.Data.SqlDbType.DateTime).Value = record.IssueDate;
        cmd.Parameters.Add("@expirationDate", System.Data.SqlDbType.DateTime).Value = record.ExpirationDate;
        cmd.Parameters.Add("@notes", System.Data.SqlDbType.NVarChar).Value = (object?)record.Notes ?? DBNull.Value;
        cmd.Parameters.Add("@paidFees", System.Data.SqlDbType.Decimal).Value = record.PaidFees;
        cmd.Parameters.Add("@isActive", System.Data.SqlDbType.Bit).Value = record.IsActive;
        cmd.Parameters.Add("@issueReason", System.Data.SqlDbType.Int).Value = record.IssueReason;
        cmd.Parameters.Add("@createdByUserId", System.Data.SqlDbType.Int).Value = record.CreatedByUserId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        return Convert.ToInt32(result);
    }
}
