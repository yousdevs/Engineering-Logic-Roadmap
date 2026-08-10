using Microsoft.Data.SqlClient;

namespace Data;

public static class TestTypeData
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
            throw new InvalidOperationException("TestTypeData not initialized, call Initialize() first.");
        }
    }

    public static async Task<IReadOnlyList<TestTypeRecord>> FindAllAsync()
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT 
                TestTypeID,
                TestTypeTitle,
                TestTypeDescription,
                TestTypeFees
            FROM TestTypes;
        ";

        await using var cmd = new SqlCommand(query, con);

        await con.OpenAsync();
        await using var reader = await cmd.ExecuteReaderAsync();

        var items = new List<TestTypeRecord>();


        while (await reader.ReadAsync())
        {

            items.Add(new TestTypeRecord(
                (int)reader["TestTypeID"],
                (string)reader["TestTypeTitle"],
                (string)reader["TestTypeDescription"],
                (decimal)reader["TestTypeFees"]
                ));
        }

        return items;

    }

    public static async Task<TestTypeRecord?> FindByIdAsync(int id)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT 
                TestTypeID,
                TestTypeTitle,
                TestTypeDescription,
                TestTypeFees
            FROM TestTypes
            WHERE TestTypeID = @id;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = id;

        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        if (!await reader.ReadAsync())
            return null;

        return new TestTypeRecord(
                (int)reader["TestTypeID"],
                (string)reader["TestTypeTitle"],
                (string)reader["TestTypeDescription"],
                (decimal)reader["TestTypeFees"]
            );
    }

    public static async Task<bool> UpdateAsync(TestTypeRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

           UPDATE TestTypes
           SET 
                TestTypeTitle = @title,
                TestTypeDescription = @description,
                TestTypeFees = @fees
            WHERE TestTypeID = @id;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@title", System.Data.SqlDbType.NVarChar).Value = record.Title;
        cmd.Parameters.Add("@description", System.Data.SqlDbType.NVarChar).Value = record.Description;
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = record.Id;
        var feeParameter = cmd.Parameters.Add("@fees", System.Data.SqlDbType.Decimal);
        feeParameter.Precision = 19;
        feeParameter.Scale = 2;
        feeParameter.Value = record.Fee;

        await con.OpenAsync();

        int affected = await cmd.ExecuteNonQueryAsync();

        return affected > 0;
    }
}
