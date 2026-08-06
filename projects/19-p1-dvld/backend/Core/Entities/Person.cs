namespace Core.Entities;

public enum Gender
{
    Male = 0,
    Female = 1
}
public sealed class Person
{
    public int Id { get; internal set; }
    public string FirstName { get; private set; }
    public string SecondName { get; private set; }
    public string? ThirdName { get; private set; }
    public string LastName { get; private set; }
    public Gender Gender { get; private set; }
    public DateTime DateOfBirth { get; private set; }
    public string NationalNo { get; private set; }
    public short NationalityCountryId { get; private set; }
    public string Address { get; private set; }
    public string PhoneNumber { get; private set; }
    public string? Email { get; private set; }
    public string? ImagePath { get; private set; }

    private const int MinAge = 18;

    private Person(int id, string firstName, string secondName, string? thirdName, string lastName, Gender gender, DateTime dateOfBirth,
        string nationalNo, short nationalityCountryId, string address, string phoneNumber, string? email, string? imagePath)
    {
        Id = id;
        FirstName = firstName;
        SecondName = secondName;
        ThirdName = thirdName;
        LastName = lastName;
        Gender = gender;
        DateOfBirth = dateOfBirth;
        NationalNo = nationalNo;
        NationalityCountryId = nationalityCountryId;
        Address = address;
        PhoneNumber = phoneNumber;
        Email = email;
        ImagePath = imagePath;
    }



    public static Person Create(string firstName, string secondName,
        string? thirdName, string lastName, Gender gender, DateTime dateOfBirth,
        string nationalNo, short nationalityCountryId, string address, string phoneNumber, string? email)
    {


        Validate("Person::Create", firstName, secondName, thirdName, lastName,
            dateOfBirth, nationalNo, nationalityCountryId, address, phoneNumber, email);

        return new Person(-1, firstName, secondName, thirdName,
            lastName, gender, dateOfBirth, nationalNo,
            nationalityCountryId, address, phoneNumber, email, null);
    }
    public static Person Reconstitute(int id, string firstName, string secondName,
        string? thirdName, string lastName, Gender gender, DateTime dateOfBirth,
        string nationalNo, short nationalityCountryId, string address, string phoneNumber, string? email, string? imagePath)
    {

        return new Person(id, firstName, secondName, thirdName,
            lastName, gender, dateOfBirth, nationalNo,
            nationalityCountryId, address, phoneNumber, email, imagePath);
    }


    public void UpdatePersonalInfo(string firstName, string secondName, string? thirdName, string lastName,
        Gender gender, DateTime dateOfBirth, string nationalNo, short nationalityCountryId,
        string address, string phoneNumber, string? email)
    {


        Validate("Person::UpdatePersonalInfo", firstName, secondName, thirdName, lastName,
            dateOfBirth, nationalNo, nationalityCountryId, address, phoneNumber, email);

        FirstName = firstName;
        SecondName = secondName;
        ThirdName = thirdName;
        LastName = lastName;
        Gender = gender;
        DateOfBirth = dateOfBirth;
        NationalNo = nationalNo;
        NationalityCountryId = nationalityCountryId;
        Address = address;
        PhoneNumber = phoneNumber;
        Email = email;

    }

    public void ChangeImage(string newImagePath)
    {
        Guard.RequireNonEmpty(newImagePath, nameof(newImagePath), "Person::ChangeImage");
        ImagePath = newImagePath;
    }

    public void RemoveImage()
    {
        if (ImagePath == null) return;

        ImagePath = null;
    }

    private static void Validate(string context, string firstName, string secondName, string? thirdName, string lastName,
         DateTime dateOfBirth, string nationalNo, short nationalityCountryId,
        string address, string phoneNumber, string? email)
    {
        Guard.RequireNonEmpty(firstName, nameof(firstName), context);
        Guard.RequireNonEmpty(secondName, nameof(secondName), context);
        Guard.RequireNonEmptyIfProvided(thirdName, nameof(thirdName), context);
        Guard.RequireNonEmpty(lastName, nameof(lastName), context);
        Guard.RequireNonEmpty(nationalNo, nameof(nationalNo), context);
        Guard.RequireNonEmpty(address, nameof(address), context);
        Guard.RequireNonEmpty(phoneNumber, nameof(phoneNumber), context);
        Guard.RequireNonEmptyIfProvided(email, nameof(email), context);

        Guard.RequireMinAge(dateOfBirth, MinAge, nameof(dateOfBirth), context);
        Guard.RequireIntegerInRange(nationalityCountryId, 1, 193, nameof(nationalityCountryId), context);
    }
}
