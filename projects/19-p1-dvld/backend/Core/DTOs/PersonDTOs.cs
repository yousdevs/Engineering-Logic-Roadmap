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

