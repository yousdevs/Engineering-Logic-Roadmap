using Microsoft.AspNetCore.Mvc;
using Microsoft.Data.SqlClient;

namespace Api.Controllers;


[ApiController]
[Route("api/[controller]")]
public sealed class CountriesController : ControllerBase
{
    public sealed record Country(int id, string name);
    public static IReadOnlyList<Country> getCountries()
    {

        var countries = new List<Country>();

        string conString = "Server=(localdb)\\MSSQLLocalDB;Database=DVLD;User Id=sa;Password=123456;TrustServerCertificate=True;";
        SqlConnection con = new SqlConnection(conString);

        string query = "SELECT * FROM Countries;";
        SqlCommand cmd = new SqlCommand(query, con);

        try
        {
            con.Open();

            var Reader = cmd.ExecuteReader();

            while (Reader.Read())
            {
                countries.Add(new Country(Reader.GetInt32(0), Reader.GetString(1)));

            }
            Reader.Close();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
            throw;
        }
        finally { con.Close(); }

        return countries;
    }



    [HttpGet]
    public ActionResult<IReadOnlyList<Country>> Get()
    {
        IReadOnlyList<Country> countries;
        try
        {
            countries = getCountries();
        }
        catch (Exception ex)
        {
            return BadRequest(ex.Message);
        }

        return Ok(countries);
    }
}