
using Microsoft.Data.SqlClient;

namespace Data;

public sealed record DetainedLicenseRecord(

    int Id,
    int LicenseId,
    DateTime DetainDate,
    decimal FineFees,
    int CreatedByUserId,
    bool IsReleased,
    DateTime? ReleaseDate,
    int? ReleasedByUserId,
    int? ReleaseApplicationId
    );

public static class DetainedLicenseData
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
            throw new InvalidOperationException("DetainedLicenseData not initialized, call Initialize() first.");
        }
    }

    public static async Task<int> InsertAsync(DetainedLicenseRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """

            INSERT INTO DetainedLicenses(
                LicenseID,
                DetainDate,
                FineFees,
                CreatedByUserID,
                IsReleased,
                ReleaseDate,
                ReleasedByUserID,
                ReleaseApplicationID
                )
            VALUES(
                @licenseId,
                @detainDate,
                @fineFees,
                @createdByUserId,
                @isReleased,
                @releaseDate,
                @releasedByUserId,
                @releaseApplicationId
                );

                SELECT CAST(SCOPE_IDENTITY() AS INT);
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@licenseId", System.Data.SqlDbType.Int).Value = record.LicenseId;
        cmd.Parameters.Add("@detainDate", System.Data.SqlDbType.DateTime).Value = record.DetainDate;
        cmd.Parameters.Add("@fineFees", System.Data.SqlDbType.Decimal).Value = record.FineFees;
        cmd.Parameters.Add("@createdByUserId", System.Data.SqlDbType.Int).Value = record.CreatedByUserId;
        cmd.Parameters.Add("@isReleased", System.Data.SqlDbType.Bit).Value = record.IsReleased;
        cmd.Parameters.Add("@releaseDate", System.Data.SqlDbType.DateTime).Value = (object?)record.ReleaseDate ?? DBNull.Value;
        cmd.Parameters.Add("@releasedByUserId", System.Data.SqlDbType.Int).Value = (object?)record.ReleasedByUserId ?? DBNull.Value;
        cmd.Parameters.Add("@releaseApplicationId", System.Data.SqlDbType.Int).Value = (object?)record.ReleaseApplicationId ?? DBNull.Value;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        return Convert.ToInt32(result);
    }

    public static async Task<bool> UpdateAsync(DetainedLicenseRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """

            UPDATE DetainedLicenses 
            SET
                LicenseID = @licenseId,
                DetainDate = @detainDate,
                FineFees = @fineFees,
                CreatedByUserID = @createdByUserId,
                IsReleased = @isReleased,
                ReleaseDate = @releaseDate,
                ReleasedByUserID = @releasedByUserId,
                ReleaseApplicationID = @releaseApplicationId
            
            WHERE DetainID = @id;
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@licenseId", System.Data.SqlDbType.Int).Value = record.LicenseId;
        cmd.Parameters.Add("@detainDate", System.Data.SqlDbType.DateTime).Value = record.DetainDate;
        cmd.Parameters.Add("@fineFees", System.Data.SqlDbType.Decimal).Value = record.FineFees;
        cmd.Parameters.Add("@createdByUserId", System.Data.SqlDbType.Int).Value = record.CreatedByUserId;
        cmd.Parameters.Add("@isReleased", System.Data.SqlDbType.Bit).Value = record.IsReleased;
        cmd.Parameters.Add("@releaseDate", System.Data.SqlDbType.DateTime).Value = (object?)record.ReleaseDate ?? DBNull.Value;
        cmd.Parameters.Add("@releasedByUserId", System.Data.SqlDbType.Int).Value = (object?)record.ReleasedByUserId ?? DBNull.Value;
        cmd.Parameters.Add("@releaseApplicationId", System.Data.SqlDbType.Int).Value = (object?)record.ReleaseApplicationId ?? DBNull.Value;
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = record.Id;

        await con.OpenAsync();

        var affected = await cmd.ExecuteNonQueryAsync();

        return affected > 0;
    }

    public static async Task<DetainedLicenseRecord?> FindByLicenseIdAsync(int licenseId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """

            SELECT DetainID,
                   DetainDate,
                   FineFees,
                   CreatedByUserID,
                   IsReleased,
                   ReleaseDate,
                   ReleasedByUserID,
                   ReleaseApplicationID
            FROM DetainedLicenses
            WHERE LicenseID = @licenseId;
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@licenseId", System.Data.SqlDbType.Int).Value = licenseId;

        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        if (!await reader.ReadAsync())
            return null;

        return new DetainedLicenseRecord(
            (int)reader["DetainID"],
            licenseId,
            (DateTime)reader["DetainDate"],
            (decimal)reader["FineFees"],
            (int)reader["CreatedByUserID"],
            (bool)reader["IsReleased"],
            reader.IsDBNull(reader.GetOrdinal("ReleaseDate")) ? null : (DateTime)reader["ReleaseDate"],
            reader.IsDBNull(reader.GetOrdinal("ReleasedByUserID")) ? null : (int)reader["ReleasedByUserID"],
            reader.IsDBNull(reader.GetOrdinal("ReleaseApplicationID")) ? null : (int)reader["ReleaseApplicationID"]
            );
    }
}
