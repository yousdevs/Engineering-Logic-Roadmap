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

public sealed record PersonDetailsRecord(

    string FirstName,
    string SecondName,
    string? ThirdName,
    string LastName,
    string NationalNo,
    DateTime DateOfBirth,
    byte Gender,
    string Phone,
    string? Email,
    string CountryName,
    string Address,
    string? ImagePath
    );