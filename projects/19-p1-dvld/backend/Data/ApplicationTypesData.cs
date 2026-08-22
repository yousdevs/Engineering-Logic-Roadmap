using Microsoft.Data.SqlClient;

namespace Data;

public static class ApplicationTypesData
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
            throw new InvalidOperationException("ApplicationTypesData not initialized, call Initialize() first.");
        }
    }

    public static async Task<IReadOnlyList<ApplicationTypeRecord>> FindAllAsync()
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT 
                ApplicationTypeID,
                ApplicationTypeTitle,
                ApplicationFees
            FROM ApplicationTypes;
        ";

        await using var cmd = new SqlCommand(query, con);

        await con.OpenAsync();
        await using var reader = await cmd.ExecuteReaderAsync();

        var items = new List<ApplicationTypeRecord>();


        while (await reader.ReadAsync())
        {

            items.Add(new ApplicationTypeRecord(
                (int)reader["ApplicationTypeID"],
                (string)reader["ApplicationTypeTitle"],
                (decimal)reader["ApplicationFees"]
                ));
        }

        return items;

    }

    public static async Task<ApplicationTypeRecord?> FindByIdAsync(int id)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT 
                ApplicationTypeID,
                ApplicationTypeTitle,
                ApplicationFees
            FROM ApplicationTypes
            WHERE ApplicationTypeID = @id;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = id;

        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        if (!await reader.ReadAsync())
            return null;

        return new ApplicationTypeRecord(
                (int)reader["ApplicationTypeID"],
                (string)reader["ApplicationTypeTitle"],
                (decimal)reader["ApplicationFees"]
            );
    }

    public static async Task<bool> UpdateAsync(ApplicationTypeRecord record)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

           UPDATE ApplicationTypes
           SET 
                ApplicationTypeTitle = @title,
                ApplicationFees = @fees
            WHERE ApplicationTypeID = @id;
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@title", System.Data.SqlDbType.NVarChar).Value = record.Title;
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = record.Id;
        var feeParameter = cmd.Parameters.Add("@fees", System.Data.SqlDbType.Decimal);
        feeParameter.Precision = 19;
        feeParameter.Scale = 2;
        feeParameter.Value = record.Fee;

        await con.OpenAsync();

        int affected = await cmd.ExecuteNonQueryAsync();

        return affected > 0;
    }

    public static async Task<decimal> GetFeesByIdAsync(int applicationTypeId)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = """

            SELECT ApplicationFees
            FROM ApplicationTypes
            WHERE ApplicationTypeID = @id;
            """;

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = applicationTypeId;

        await con.OpenAsync();

        var result = await cmd.ExecuteScalarAsync();

        return Convert.ToDecimal(result);
    }
}
