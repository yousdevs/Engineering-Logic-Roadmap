using Microsoft.Data.SqlClient;
using System.Data;

namespace Data;

public static class TestAppointmentData
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
            throw new InvalidOperationException("TestAppointmentData not initialized, call Initialize() first.");
        }
    }

    public static async Task<IReadOnlyList<TestAttemptRecord>> GetHistoryAsync(int localDrivingLicenseApplicationId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT a.TestAppointmentID,
                   a.TestTypeID,
                   t.TestResult
            FROM TestAppointments a
            LEFT JOIN Tests t
            ON a.TestAppointmentID = t.TestAppointmentID
            WHERE a.LocalDrivingLicenseApplicationID = @id
            ORDER BY a.TestAppointmentID;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = localDrivingLicenseApplicationId;

        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        var records = new List<TestAttemptRecord>();
        while (await reader.ReadAsync())
        {
            records.Add(new TestAttemptRecord(

                (int)reader["TestAppointmentID"],
                (int)reader["TestTypeID"],
                reader.IsDBNull(reader.GetOrdinal("TestResult")) ? null : (bool)reader["TestResult"]
                ));
        }

        return records;
    }

    public static async Task<int?> InsertAppointmentAsync(TestAppointmentRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            INSERT INTO TestAppointments 
                (TestTypeID, 
                 LocalDrivingLicenseApplicationID,
                 AppointmentDate,
                 PaidFees,
                 CreatedByUserID,
                 IsLocked,
                 RetakeTestApplicationID)
            VALUES(
                @testTypeId,
                @localDrivingLicenseApplicationId,
                @appointmentDate,
                @paidFees,
                @createdByUserId,
                @isLocked,
                @retakeTestApplicationId
            );
            SELECT CAST(SCOPE_IDENTITY() AS INT);
        ";

        await using var cmd = new SqlCommand(query, con);

        cmd.Parameters.Add("@testTypeId", System.Data.SqlDbType.Int).Value = record.TestTypeId;
        cmd.Parameters.Add("@localDrivingLicenseApplicationId", System.Data.SqlDbType.Int).Value = record.LocalDrivingLicenseApplicationId;
        cmd.Parameters.Add("@appointmentDate", System.Data.SqlDbType.DateTime).Value = record.AppointmentDate;
        cmd.Parameters.Add("@paidFees", System.Data.SqlDbType.Decimal).Value = record.PaidFees;
        cmd.Parameters.Add("@createdByUserId", System.Data.SqlDbType.Int).Value = record.CreatedByUserId;
        cmd.Parameters.Add("@isLocked", System.Data.SqlDbType.Bit).Value = record.IsLocked;
        cmd.Parameters.Add("@retakeTestApplicationId", SqlDbType.Int).Value = (object?)record.RetakeTestApplicationId ?? DBNull.Value;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        if (result == null)
            return null;


        return (int)result;
    }

    public static async Task<TestAppointmentRecord?> FindAppointmentByIdAsync(int appointmentId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """

            SELECT 
                TestAppointmentID,
                TestTypeID,
                LocalDrivingLicenseApplicationID,
                AppointmentDate,
                PaidFees,
                CreatedByUserID,
                IsLocked,
                RetakeTestApplicationID
            FROM TestAppointments
            WHERE TestAppointmentID = @id;
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@id", SqlDbType.Int).Value = appointmentId;

        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        if (!await reader.ReadAsync())
            return null;

        return new TestAppointmentRecord(
                appointmentId,
                (int)reader["TestTypeID"],
                (int)reader["LocalDrivingLicenseApplicationID"],
                (DateTime)reader["AppointmentDate"],
                (decimal)reader["PaidFees"],
                (int)reader["CreatedByUserID"],
                (bool)reader["IsLocked"],
                reader.IsDBNull(reader.GetOrdinal("RetakeTestApplicationID")) ? null : (int)reader["RetakeTestApplicationID"]
            );

    }


    public static async Task<int?> InsertTestAsync(TestRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            INSERT INTO Tests 
                (
                 TestAppointmentID,
                 TestResult,
                 Notes,
                 CreatedByUserID)
            VALUES(
                @testAppointmentId,
                @testResult,
                @notes,
                @createdByUserId
            );
            SELECT CAST(SCOPE_IDENTITY() AS INT);
        ";

        await using var cmd = new SqlCommand(query, con);

        cmd.Parameters.Add("@testAppointmentId", System.Data.SqlDbType.Int).Value = record.TestAppointmentId;
        cmd.Parameters.Add("@testResult", System.Data.SqlDbType.Bit).Value = record.TestResult;
        cmd.Parameters.Add("@notes", System.Data.SqlDbType.NVarChar).Value = (object?)record.Notes ?? DBNull.Value;
        cmd.Parameters.Add("@createdByUserId", System.Data.SqlDbType.Int).Value = record.CreatedByUserId;


        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        if (result == null)
            return null;


        return (int)result;
    }

    public static async Task<bool> UpdateTestAppointmentAsync(TestAppointmentRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """

            UPDATE TestAppointments
            SET TestTypeID = @testTypeId,
            LocalDrivingLicenseApplicationID = @localDrivingLicenseApplicationId,
            AppointmentDate = @appointmentDate,
            PaidFees = @paidFees,
            CreatedByUserID = @createdByUserId,
            IsLocked = @isLocked,
            RetakeTestApplicationID = @retakeTestApplicationId
            
            WHERE TestAppointmentID = @id;
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@testTypeId", SqlDbType.Int).Value = record.TestTypeId;
        cmd.Parameters.Add("@localDrivingLicenseApplicationId", SqlDbType.Int).Value = record.LocalDrivingLicenseApplicationId;
        cmd.Parameters.Add("@appointmentDate", SqlDbType.DateTime).Value = record.AppointmentDate;
        cmd.Parameters.Add("@paidFees", SqlDbType.Decimal).Value = record.PaidFees;
        cmd.Parameters.Add("@createdByUserId", SqlDbType.Int).Value = record.CreatedByUserId;
        cmd.Parameters.Add("@isLocked", SqlDbType.Bit).Value = record.IsLocked;
        cmd.Parameters.Add("@retakeTestApplicationId", SqlDbType.Int).Value = (object?)record.RetakeTestApplicationId ?? DBNull.Value;
        cmd.Parameters.Add("@id", SqlDbType.Int).Value = record.Id;

        await con.OpenAsync();

        int affected = await cmd.ExecuteNonQueryAsync();

        return (affected > 0);
    }
}
