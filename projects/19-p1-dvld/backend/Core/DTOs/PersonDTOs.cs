namespace Core.DTOs;

public sealed record PersonSummary(
    int personId,
    string nationalNo,
    string firstName,
    string secondName,
    string? thirdName,
    string lastName,
    string gender,
    DateTime dateOfBirth,
    string nationality,
    string phoneNumber,
    string? email
    );

public sealed record PersonForm(
    string NationalNo,
    string FirstName,
    string SecondName,
    string? ThirdName,
    string LastName,
    string Gender,
    DateTime DateOfBirth,
    int NationalityCountryId,
    string PhoneNumber,
    string? Email,
    string Address
    );
