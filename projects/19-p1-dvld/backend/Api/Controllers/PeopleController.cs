using Microsoft.AspNetCore.Mvc;
using Microsoft.Data.SqlClient;
using System.Data;
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

        private readonly IWebHostEnvironment _environment;

        public PeopleController(IWebHostEnvironment environment)
        {
            _environment = environment;
        }

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


        public sealed record CreatePersonResponse(int id);

        public enum ImageAction { Unchanged, Replaced, Removed }

        public sealed class ImageUpdateRequest
        {
            public required ImageAction Action { get; init; }
            public IFormFile? File { get; init; }
        }
        public sealed class CreatePersonRequest
        {
            public required string NationalNo { get; init; }

            public required string FirstName { get; init; }

            public required string SecondName { get; init; }

            public string? ThirdName { get; init; }

            public required string LastName { get; init; }

            public byte Gender { get; init; }

            public required DateOnly DateOfBirth { get; init; }

            public int NationalityCountryId { get; init; }

            public string? Email { get; init; }

            public required string phoneNumber { get; init; }

            public required string Address { get; init; }

            public ImageUpdateRequest? Image { get; init; }

        }

        public static int CreatePersonDB(CreatePersonRequest req, string? imagePath)
        {
            string conString = "Server=(localdb)\\MSSQLLocalDB;Database=DVLD;User Id=sa;Password=123456;TrustServerCertificate=True;";

            using var con = new SqlConnection(conString);

            string query = @"INSERT INTO People VALUES
                (@NationalNo, @FirstName, @SecondName, @ThirdName, @LastName,  @DateOfBirth, @Gender, @Address, @PhoneNumber, @Email, @NationalityCountryId, @ImagePath);
                        SELECT CAST(SCOPE_IDENTITY() AS INT);";

            using var cmd = new SqlCommand(query, con);
            cmd.Parameters.AddWithValue("@NationalNo", req.NationalNo);
            cmd.Parameters.AddWithValue("@FirstName", req.FirstName);
            cmd.Parameters.AddWithValue("@SecondName", req.SecondName);
            if (req.ThirdName != null)
            {
                cmd.Parameters.AddWithValue("@ThirdName", req.ThirdName);
            }
            else
            {
                cmd.Parameters.AddWithValue("@ThirdName", System.DBNull.Value);
            }
            cmd.Parameters.AddWithValue("@LastName", req.LastName);
            cmd.Parameters.AddWithValue("@DateOfBirth", req.DateOfBirth);
            cmd.Parameters.AddWithValue("@Gender", req.Gender);
            cmd.Parameters.AddWithValue("@Address", req.Address);
            cmd.Parameters.AddWithValue("@PhoneNumber", req.phoneNumber);

            if (req.Email != null)
            {
                cmd.Parameters.AddWithValue("@Email", req.Email);
            }
            else
            {
                cmd.Parameters.AddWithValue("@Email", System.DBNull.Value);
            }
            cmd.Parameters.AddWithValue("@NationalityCountryId", req.NationalityCountryId);

            cmd.Parameters.Add("@ImagePath", SqlDbType.NVarChar).Value = (object?)imagePath ?? DBNull.Value;

            con.Open();
            int id = (int)cmd.ExecuteScalar();
            return id;
        }

        public static string? SaveImage(IFormFile? image, string webRootPath)
        {
            if (image is null || image.Length == 0) return null;

            var uploadsDirectory = Path.Combine(

                webRootPath,
                "images",
                "people"

                );

            Directory.CreateDirectory(uploadsDirectory);

            var extension = Path.GetExtension(image.FileName);
            var fileName = $"{Guid.NewGuid()}{extension}";

            var physicalPath = Path.Combine(uploadsDirectory, fileName);


            using var stream = System.IO.File.Create(physicalPath);

            image.CopyTo(stream);

            return Path.Combine("images", "people", fileName).Replace('\\', '/');
        }

        [HttpPost]
        public ActionResult<CreatePersonResponse> CreatePerson([FromForm] CreatePersonRequest request)
        {

            int id;
            CreatePersonResponse res;
            string? imagePath = null;
            if (request.Image is not null && request.Image.Action == ImageAction.Replaced && request.Image.File is not null)
            {
                imagePath = SaveImage(request.Image.File, _environment.WebRootPath);
            }

            try
            {
                id = CreatePersonDB(request, imagePath);
                res = new CreatePersonResponse(id);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }




            return Created(
                 $"/api/people/{res.id}",
                     res);
        }



        public sealed record PersonDetails(int id, string firstName, string secondName, string? thirdName, string lastName, string nationalNo,
            DateTime dateOfBirth, byte gender, string phoneNumber, string? email, string country, string address, string? imagePath);


        public static PersonDetails GetPersonDB(int id)
        {

            string conString = "Server=(localdb)\\MSSQLLocalDB;Database=DVLD;User Id=sa;Password=123456;TrustServerCertificate=True;";

            using var con = new SqlConnection(conString);

            string query = @"SELECT 
                            p.PersonID,
                            p.FirstName,
                            p.SecondName,
                            p.ThirdName,
                            p.LastName,
                            p.NationalNo,
                            p.DateOfBirth,
                            p.Gendor,
                            p.Phone,
                            p.Email,
                            c.CountryName,
                            p.Address,
                            p.ImagePath
                            FROM People p
                            INNER JOIN Countries c
                            ON p.NationalityCountryID = c.CountryID
                            WHERE PersonID = @PersonID;";
            using var cmd = new SqlCommand(query, con);
            cmd.Parameters.AddWithValue("@PersonID", id);

            con.Open();

            var reader = cmd.ExecuteReader();

            reader.Read();

            return new PersonDetails((int)reader["PersonID"], (string)reader["FirstName"], (string)reader["SecondName"],
                reader.IsDBNull(reader.GetOrdinal("ThirdName")) ? null : reader.GetString(reader.GetOrdinal("ThirdName")), (string)reader["LastName"],
                (string)reader["NationalNo"], (DateTime)reader["DateOfBirth"], (byte)reader["Gendor"], (string)reader["Phone"],
                reader.IsDBNull(reader.GetOrdinal("Email")) ? null : reader.GetString(reader.GetOrdinal("Email")), (string)reader["CountryName"],
                (string)reader["Address"],
                reader.IsDBNull(reader.GetOrdinal("ImagePath")) ? null : reader.GetString(reader.GetOrdinal("ImagePath")));
        }

        [HttpGet("{id:int}")]
        public ActionResult<PersonDetails> GetPersonDetails(int id)
        {
            PersonDetails person;
            try
            {
                person = GetPersonDB(id);
            }
            catch (Exception ex)
            {
                return NotFound(ex.Message);
            }

            return Ok(person);
        }


        public sealed class EditPersonRequest
        {
            public required string NationalNo { get; init; }

            public required string FirstName { get; init; }

            public required string SecondName { get; init; }

            public string? ThirdName { get; init; }

            public required string LastName { get; init; }

            public byte Gender { get; init; }

            public required DateOnly DateOfBirth { get; init; }

            public int NationalityCountryId { get; init; }

            public string? Email { get; init; }

            public required string phoneNumber { get; init; }

            public required string Address { get; init; }

            public ImageUpdateRequest? Image { get; init; }

        }

        public sealed record EditPersonResponse(int id);


        public static int EditPersonDB(EditPersonRequest request, int id, string? imagePath, bool imageRemoved)
        {

            string conString = "Server=(localdb)\\MSSQLLocalDB;Database=DVLD;User Id=sa;Password=123456;TrustServerCertificate=True;";

            using var con = new SqlConnection(conString);


            // the queryBuilder need to know wether 
            // set existing ImagePath to null, 
            // or change it to new @ImagePath,
            // or keep it as is

            string query = @"
                    
                UPDATE People
                SET
                NationalNo = @NationalNo,
                FirstName = @FirstName,
                SecondName = @SecondName,
                ThirdName = @ThirdName,
                LastName = @LastName,
                Gendor = @Gender,
                DateOfBirth = @DateOfBirth,
                Address = @Address,
                Phone = @PhoneNumber,
                Email = @Email,
                NationalityCountryID = @NationalityCountryID
                ";
            if (imageRemoved)
            {
                query += @", ImagePath = NULL";
            }
            else if (imagePath is not null)
            {
                query += ", ImagePath = @ImagePath";
            }

            query += " WHERE PersonID = @PersonID";

            using var cmd = new SqlCommand(query, con);

            cmd.Parameters.AddWithValue("@NationalNo", request.NationalNo);
            cmd.Parameters.AddWithValue("@FirstName", request.FirstName);
            cmd.Parameters.AddWithValue("@SecondName", request.SecondName);
            cmd.Parameters.AddWithValue("@ThirdName", request.ThirdName is not null ? request.ThirdName : DBNull.Value);
            cmd.Parameters.AddWithValue("@LastName", request.LastName);
            cmd.Parameters.AddWithValue("@Gender", request.Gender);
            cmd.Parameters.AddWithValue("@DateOfBirth", request.DateOfBirth);
            cmd.Parameters.AddWithValue("@Address", request.Address);
            cmd.Parameters.AddWithValue("@PhoneNumber", request.phoneNumber);
            cmd.Parameters.AddWithValue("@Email", request.Email is not null ? request.Email : DBNull.Value);
            cmd.Parameters.AddWithValue("@NationalityCountryID", request.NationalityCountryId);

            if (imagePath is not null)
            {
                cmd.Parameters.AddWithValue("@ImagePath", imagePath);
            }

            cmd.Parameters.AddWithValue("@PersonID", id);

            con.Open();

            int affected = cmd.ExecuteNonQuery();

            if (affected < 0)
            {
                throw new Exception("couldn't update person");
            }

            return id;

        }

        public static string? getImagePathById(int id)
        {

            string conString = "Server=(localdb)\\MSSQLLocalDB;Database=DVLD;User Id=sa;Password=123456;TrustServerCertificate=True;";

            using var con = new SqlConnection(conString);

            string query = "SELECT ImagePath FROM People WHERE PersonID = @PersonID;";

            using var cmd = new SqlCommand(query, con);

            cmd.Parameters.AddWithValue("@PersonID", id);


            con.Open();

            var reader = cmd.ExecuteReader();

            reader.Read();

            if (reader.IsDBNull(0))
            {
                return null;
            }
            return (string)reader[0];
        }


        public static void RemoveImage(string path)
        {


            System.IO.File.Delete(Path.Combine("wwwroot", path));

        }



        [HttpPut("{id:int}")]
        public ActionResult<EditPersonResponse> EditPerson([FromForm] EditPersonRequest request, int id)
        {


            // now i have the request
            // 1- we extract the image state

            var imageState = request.Image;

            // replaced, removed, unchanged
            // replaced- the existing image should be deleted from server, then update imagepath in db with the new saved image
            // we can, get the existing image path from db, then we save the new image with same path, this will replace the image while keeping the imagepath unchanged.
            // but since the remove function will be reusable, we stick to delete the existing image from server, then save the new one and update dbpath.

            // removed- we must set the db image path to null, delete the existing image from server.

            // unchanged- we don't touch the image path on db.


            string? imagePath = null;

            bool imageRemoved = false;

            switch (imageState.Action)
            {
                case (ImageAction.Removed):
                    RemoveImage(getImagePathById(id));
                    imagePath = null;
                    imageRemoved = true;
                    break;
                case ImageAction.Replaced:
                    string? path = getImagePathById(id);
                    if (path is not null)
                    {
                        RemoveImage(path);
                    }


                    imagePath = SaveImage(imageState.File, _environment.WebRootPath);
                    imageRemoved = false;
                    break;
                case ImageAction.Unchanged:
                    imagePath = null;
                    imageRemoved = false;
                    break;
                default: return BadRequest("Unsupported imageaction state");

            }

            try
            {
                EditPersonDB(request, id, imagePath, imageRemoved);
            }
            catch (Exception ex)
            {

                return BadRequest(ex.Message);
            }
            return Ok(new EditPersonResponse(id));


        }


        public static void DeletePersonDB(int id)
        {

            string conString = "Server=(localdb)\\MSSQLLocalDB;Database=DVLD;User Id=sa;Password=123456;TrustServerCertificate=True;";

            using var con = new SqlConnection(conString);

            string query = "DELETE FROM People WHERE PersonID = @PersonID;";

            using var cmd = new SqlCommand(query, con);

            cmd.Parameters.AddWithValue("@PersonID", id);

            con.Open();
            int affected = cmd.ExecuteNonQuery();

            if (affected == 0) throw new Exception("Couldn't delete person with id = " + id);
        }

        [HttpDelete("{id:int}")]
        public ActionResult DeletePerson(int id)
        {

            // get image path by id
            // delete person from db
            // if success remove the image.

            string? imagePath = getImagePathById(id);

            try
            {
                DeletePersonDB(id);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }

            if (imagePath is not null) RemoveImage(imagePath);

            return NoContent();

        }

    }


}
