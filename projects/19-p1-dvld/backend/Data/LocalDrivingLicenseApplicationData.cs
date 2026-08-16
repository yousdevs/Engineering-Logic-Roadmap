using Microsoft.Data.SqlClient;

namespace Data;

public static class LocalDrivingLicenseApplicationData
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
            throw new InvalidOperationException("LocalDrivingLicenseApplicationData not initialized, call Initialize() first.");
        }
    }

    public static async Task<int?> InsertAsync(int applicationId, int licenseClassId)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            INSERT INTO LocalDrivingLicenseApplications(
                    ApplicationID,
                    LicenseClassID)
            VALUES(
                @applicationId,
                @licenseClassId
                );
            SELECT CAST(SCOPE_IDENTITY() AS INT);
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@applicationId", System.Data.SqlDbType.Int).Value = applicationId;
        cmd.Parameters.Add("@licenseClassId", System.Data.SqlDbType.Int).Value = licenseClassId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        if (result == null)
            return null;

        return (int)result;
    }

    public static async Task<int?> GetIdByApplicationId(int applicationId)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            
            SELECT LocalDrivingLicenseApplicationID 
            FROM LocalDrivingLicenseApplications
            WHERE ApplicationID = @id;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = applicationId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        if (result == null)
            return null;

        return (int)result;
    }

    public static async Task<int?> GetApplicationStatusByIdAsync(int localDrivingLicenseApplicationId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """
            SELECT ApplicationStatus 
            FROM LocalDrivingLicenseApplications l
            INNER JOIN Applications a
            ON l.ApplicationID = a.ApplicationID
            WHERE l.LocalDrivingLicenseApplicationID = @id;
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = localDrivingLicenseApplicationId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        return result == null ? null : Convert.ToInt32((byte)result);

    }
}
