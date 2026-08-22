using Microsoft.Data.SqlClient;

namespace Data;

public static class LicenseClassData
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
            throw new InvalidOperationException("LicenseClassData not initialized, call Initialize() first.");
        }
    }

    public static async Task<IReadOnlyList<LicenseClassRecord>> FindAllAsync()
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"

            SELECT 
                LicenseClassID,
                ClassName,
                ClassDescription,
                MinimumAllowedAge,
                DefaultValidityLength,
                ClassFees
            FROM LicenseClasses;
        ";

        await using var cmd = new SqlCommand(query, con);

        await con.OpenAsync();
        await using var reader = await cmd.ExecuteReaderAsync();

        var items = new List<LicenseClassRecord>();


        while (await reader.ReadAsync())
        {

            items.Add(new LicenseClassRecord(
                (int)reader["LicenseClassID"],
                (string)reader["ClassName"],
                (string)reader["ClassDescription"],
                Convert.ToInt32(reader["MinimumAllowedAge"]),
                Convert.ToInt32(reader["DefaultValidityLength"]),
                (decimal)reader["ClassFees"]
                ));
        }

        return items;

    }

    public static async Task<LicenseClassRecord?> FindByIdAsync(int id)
    {
        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            SELECT 
                LicenseClassID,
                ClassName,
                ClassDescription,
                MinimumAllowedAge,
                DefaultValidityLength,
                ClassFees
            FROM LicenseClasses
            WHERE LicenseClassID = @id;
            
        ";

        await using var cmd = new SqlCommand(query, con);
        cmd.Parameters.Add("@id", System.Data.SqlDbType.Int).Value = id;

        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        if (!await reader.ReadAsync())
            return null;

        return new LicenseClassRecord(
                (int)reader["LicenseClassID"],
                (string)reader["ClassName"],
                (string)reader["ClassDescription"],
                Convert.ToInt32(reader["MinimumAllowedAge"]),
                Convert.ToInt32(reader["DefaultValidityLength"]),
                (decimal)reader["ClassFees"]
                );
    }
}
