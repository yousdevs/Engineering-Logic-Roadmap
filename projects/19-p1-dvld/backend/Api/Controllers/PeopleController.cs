using Microsoft.AspNetCore.Mvc;
using Microsoft.Data.SqlClient;
public class PersonDto
{
    public int Id { get; set; }
    public string NationalNo { get; set; }
    public string FirstName { get; set; }
    public string SecondName { get; set; }
    public string ThirdName { get; set; }
    public string LastName { get; set; }
    public string Gender { get; set; }
    public DateTime DateOfBirth { get; set; }
    public string Nationality { get; set; }
    public string PhoneNumber { get; set; }
    public string Email { get; set; }

    public PersonDto(int Id, string NationalNo, string FirstName, string SecondName, string ThirdName, string LastName, string Gender, DateTime DateOfBirth, string Nationality, string PhoneNumber, string Email)
    {

        this.Id = Id;
        this.NationalNo = NationalNo;
        this.FirstName = FirstName;
        this.SecondName = SecondName;
        this.ThirdName = ThirdName;
        this.LastName = LastName;
        this.Gender = Gender;
        this.DateOfBirth = DateOfBirth;
        this.Nationality = Nationality;
        this.PhoneNumber = PhoneNumber;
        this.Email = Email;
    }
}
namespace Api.Controllers
{
    public sealed record PagedResult<T>(int offset, int limit, int total, IReadOnlyList<T> items);

    [Route("api/[controller]")]
    [ApiController]
    public class PeopleController : ControllerBase
    {

        public static PagedResult<PersonDto> getPeople(int offset, int limit)
        {
            const string conString = "Server=(localdb)\\MSSQLLocalDB;Database=DVLD;User Id=sa;Password=123456;TrustServerCertificate=True;";
            SqlConnection con = new SqlConnection(conString);

            const string query = "SELECT COUNT(*) FROM People; SELECT * FROM People p INNER JOIN Countries c ON p.NationalityCountryID = c.CountryID ORDER BY PersonID OFFSET @offset ROWS FETCH NEXT @limit ROWS ONLY;";

            SqlCommand cmd = new SqlCommand(query, con);
            cmd.Parameters.AddWithValue("@offset", offset);
            cmd.Parameters.AddWithValue("@limit", limit);
            var people = new List<PersonDto>();
            int total = 0;
            try
            {

                con.Open();
                SqlDataReader reader = cmd.ExecuteReader();

                reader.Read();
                total = reader.GetInt32(0);
                reader.NextResult();

                int idOrdinal = reader.GetOrdinal("PersonID");
                int nationalNoOrdinal = reader.GetOrdinal("NationalNo");
                int firstNameOrdinal = reader.GetOrdinal("FirstName");
                int secondNameOrdinal = reader.GetOrdinal("SecondName");
                int thirdNameOrdinal = reader.GetOrdinal("ThirdName");
                int lastNameOrdinal = reader.GetOrdinal("LastName");
                int genderOrdinal = reader.GetOrdinal("Gendor");
                int dateOfBirthOrdinal = reader.GetOrdinal("DateOfBirth");
                int nationalityOrdinal = reader.GetOrdinal("CountryName");
                int phoneNumberOrdinal = reader.GetOrdinal("Phone");
                int emailOrdinal = reader.GetOrdinal("Email");

                while (reader.Read())
                {

                    people.Add(
                        new PersonDto(
                        reader.GetInt32(idOrdinal),
                        reader.GetString(nationalNoOrdinal),
                        reader.GetString(firstNameOrdinal),
                        reader.GetString(secondNameOrdinal),
                        reader.IsDBNull(thirdNameOrdinal) ? "null" : reader.GetString(thirdNameOrdinal),
                        reader.GetString(lastNameOrdinal),
                        (reader.GetByte(genderOrdinal) == 1 ? "Female" : "Male"),
                        reader.GetDateTime(dateOfBirthOrdinal),
                        reader.GetString(nationalityOrdinal),
                        reader.GetString(phoneNumberOrdinal),
                        reader.IsDBNull(emailOrdinal) ? "test@test.com" : reader.GetString(emailOrdinal)
                        ));

                }
                reader.Close();
            }
            catch (Exception ex)
            {

                Console.WriteLine(ex.Message);

            }
            finally
            {
                con.Close();
            }

            var res = new PagedResult<PersonDto>(offset, limit, total, people);

            return res;
        }

        [HttpGet]
        public ActionResult<PagedResult<PersonDto>> GetPeople(int offset, int limit)
        {


            var people = getPeople(offset, limit);



            return Ok(people);
        }



        public static bool getPersonExistsByNationalNo(string nationalNo)
        {

            string query = "SELECT CASE WHEN EXISTS (SELECT 1 FROM People WHERE NationalNo=@NationalNo) THEN CAST(1 AS bit) ELSE CAST(0 AS bit) END AS EXIST;";

            const string conString = "Server=(localdb)\\MSSQLLocalDB;Database=DVLD;User Id=sa;Password=123456;TrustServerCertificate=True;";
            SqlConnection con = new SqlConnection(conString);

            SqlCommand cmd = new SqlCommand(query, con);
            cmd.Parameters.AddWithValue("@NationalNo", nationalNo);

            bool Exists;
            try
            {
                con.Open();
                var Reader = cmd.ExecuteReader();

                Reader.Read();
                Exists = Reader.GetBoolean(0);


                Reader.Close();
            }
            catch (Exception ex)
            {

                Console.WriteLine(ex.ToString());
                throw;
            }
            finally { con.Close(); }

            return Exists;
        }

        public sealed record AvailabilityResponse(bool Exists);
        [HttpGet("availability")]
        public ActionResult<AvailabilityResponse> CheckNationalNumberAvailability([FromQuery] string nationalNo)
        {

            try
            {
                return new AvailabilityResponse(getPersonExistsByNationalNo(nationalNo));
            }
            catch (Exception ex)
            {

                return BadRequest(ex.ToString());
            }
        }
    }
}
