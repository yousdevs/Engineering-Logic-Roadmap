using Microsoft.Data.SqlClient;

namespace Data;

public static class ApplicationData
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
            throw new InvalidOperationException("ApplicationData not initialized, call Initialize() first.");
        }
    }

    public static async Task<bool> ExistsNewOrCompletedByPersonIdAndApplicationTypeIdAndLicenseClassIdAsync(int personId, int applicationTypeId, int licenseClassId)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT CAST(
                CASE WHEN EXISTS (
                    SELECT 1
                    FROM Applications A
                    INNER JOIN LocalDrivingLicenseApplications L
                    ON A.ApplicationID = L.ApplicationID
                    WHERE A.ApplicantPersonID = @personId
                      AND A.ApplicationTypeID = @applicationTypeId
                      AND A.ApplicationStatus IN (1, 3)
                      AND L.LicenseClassID = @licenseClassId
                )
                THEN 1
                ELSE 0
                END
                AS bit);
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@personId", System.Data.SqlDbType.Int).Value = personId;
        cmd.Parameters.Add("@applicationTypeId", System.Data.SqlDbType.Int).Value = applicationTypeId;
        cmd.Parameters.Add("@licenseClassID", System.Data.SqlDbType.Int).Value = licenseClassId;
        await con.OpenAsync();

        bool exists = Convert.ToBoolean(await cmd.ExecuteScalarAsync());

        return exists;
    }

    public static async Task<int?> InsertAsync(ApplicationRecord application)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            INSERT INTO Applications(
                    ApplicantPersonID,
                    ApplicationDate,
                    ApplicationTypeID,
                    ApplicationStatus,
                    LastStatusDate,
                    PaidFees,
                    CreatedByUserID)
            VALUES(
                @personId,
                @applicationDate,
                @applicationTypeId,
                @applicationStatus,
                @lastStatusDate,
                @paidFees,
                @createdByUserId
                );
            SELECT CAST(SCOPE_IDENTITY() AS INT);
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@personId", System.Data.SqlDbType.Int).Value = application.ApplicantPersonId;
        cmd.Parameters.Add("@applicationDate", System.Data.SqlDbType.DateTime).Value = application.ApplicationDate;
        cmd.Parameters.Add("@applicationTypeId", System.Data.SqlDbType.Int).Value = application.ApplicationTypeId;
        cmd.Parameters.Add("@applicationStatus", System.Data.SqlDbType.TinyInt).Value = application.ApplicationStatus;
        cmd.Parameters.Add("@lastStatusDate", System.Data.SqlDbType.DateTime).Value = application.LastStatusDate;
        cmd.Parameters.Add("@paidFees", System.Data.SqlDbType.Decimal).Value = application.PaidFees;
        cmd.Parameters.Add("@createdByUserId", System.Data.SqlDbType.Int).Value = application.CreatedByUserId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        if (result == null)
            return null;

        return (int)result;
    }
}
