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


    public static async Task<int> InsertAsync(
        string nationalNo,
        string firstName,
        string secondName,
        string? thirdName,
        string lastName,
        DateTime dateOfBirth,
        byte gender,
        string address,
        string phoneNumber,
        string? email,
        int nationalityCountryId
        )
    {

        RequireInitialized();

        using var con = new SqlConnection(_connectionString);

        string query = @"
            INSERT INTO People (
                NationalNo,
                FirstName,
                SecondName,
                ThirdName,
                LastName,
                DateOfBirth,
                Gendor,
                Address,
                Phone,
                Email,
                NationalityCountryID,
                ImagePath
            )
            VALUES(
                @NationalNo,
                @FirstName,
                @SecondName,
                @ThirdName,
                @LastName,
                @DateOfBirth,
                @Gender,
                @Address,
                @PhoneNumber,
                @Email,
                @NationalityCountryId,
                @ImagePath);

            SELECT CAST(SCOPE_IDENTITY() AS INT);";

        using var cmd = new SqlCommand(query, con);


        cmd.Parameters.Add("@NationalNo", SqlDbType.NVarChar).Value = nationalNo;
        cmd.Parameters.Add("@FirstName", SqlDbType.NVarChar).Value = firstName;
        cmd.Parameters.Add("@SecondName", SqlDbType.NVarChar).Value = secondName;

        cmd.Parameters.Add("@ThirdName", SqlDbType.NVarChar).Value = (object?)thirdName ?? DBNull.Value;

        cmd.Parameters.Add("@LastName", SqlDbType.NVarChar).Value = lastName;
        cmd.Parameters.Add("@DateOfBirth", SqlDbType.DateTime).Value = dateOfBirth;
        cmd.Parameters.Add("@Gender", SqlDbType.TinyInt).Value = gender;
        cmd.Parameters.Add("@Address", SqlDbType.NVarChar).Value = address;
        cmd.Parameters.Add("@PhoneNumber", SqlDbType.NVarChar).Value = phoneNumber;

        cmd.Parameters.Add("@Email", SqlDbType.NVarChar).Value = (object?)email ?? DBNull.Value;

        cmd.Parameters.Add("@NationalityCountryId", SqlDbType.Int).Value = nationalityCountryId;

        cmd.Parameters.Add("@ImagePath", SqlDbType.NVarChar).Value = (object?)null ?? DBNull.Value;

        await con.OpenAsync();

        int id = Convert.ToInt32(await cmd.ExecuteScalarAsync());

        return id;
    }
}
