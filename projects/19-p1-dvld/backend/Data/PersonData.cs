using Microsoft.Data.SqlClient;
using System.Data;
namespace Data;

public delegate void PersonRowCallback(
        int personId,
        string nationalNo,
        string firstName,
        string secondName,
        string? thirdName,
        string lastName,
        byte gender,
        DateTime dateOfBirth,
        string countryName,
        string phone,
        string? email
);

public static class PersonData
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
            throw new InvalidOperationException("PersonData not initialized, call Initialize() first.");
        }
    }


    public static async Task<int> FindAllAsync(int offset, int limit, PersonRowCallback onRow)
    {

        RequireInitialized();

        await using var con = new SqlConnection(_connectionString);

        const string query = @"
            SELECT COUNT(*) FROM People;
            SELECT
            p.PersonID,
            p.NationalNo,
            p.FirstName,
            p.SecondName,
            p.ThirdName,
            p.LastName,
            p.Gendor,
            p.DateOfBirth,
            c.CountryName,
            p.Phone,
            p.Email
            FROM People p INNER JOIN Countries c
            ON p.NationalityCountryID = c.CountryID
            ORDER BY PersonID
            OFFSET @offset
            ROWS FETCH NEXT @limit ROWS ONLY;";

        await using var cmd = new SqlCommand(query, con);

        cmd.Parameters.Add("@offset", SqlDbType.Int).Value = offset;
        cmd.Parameters.Add("@limit", SqlDbType.Int).Value = limit;


        await con.OpenAsync();

        await using var reader = await cmd.ExecuteReaderAsync();

        await reader.ReadAsync();

        int totalCount = reader.GetInt32(0);

        await reader.NextResultAsync();

        while (await reader.ReadAsync())
        {

            onRow(
                (int)reader["PersonID"],
                (string)reader["NationalNo"],
                (string)reader["FirstName"],
                (string)reader["SecondName"],
                (string?)(reader.IsDBNull(reader.GetOrdinal("ThirdName")) ? null : reader["ThirdName"]),
                (string)reader["LastName"],
                (byte)reader["Gendor"],
                reader.GetDateTime(reader.GetOrdinal("DateOfBirth")),
                (string)reader["CountryName"],
                (string)reader["Phone"],
                (string?)(reader.IsDBNull(reader.GetOrdinal("Email")) ? null : reader["Email"])
                );
        }

        return totalCount;
    }
}
