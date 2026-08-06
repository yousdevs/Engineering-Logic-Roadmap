namespace Data;

public sealed record PersonRecord(

    int PersonID,
    string NationalNo,
    string FirstName,
    string SecondName,
    string? ThirdName,
    string LastName,
    DateTime DateOfBirth,
    byte Gendor,
    string Address,
    string Phone,
    string? Email,
    int NationalityCountryID,
    string? ImagePath
    );