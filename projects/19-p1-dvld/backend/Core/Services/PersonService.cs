namespace Core.Services;

using Core.DTOs;
using Core.Entities;
using Data;

public sealed class PersonService
{


    public async Task<PagedResult<PersonSummary>> GetAllAsync(Page page)
    {

        int offset = (page.Number - 1) * page.Size;

        var people = new List<PersonSummary>();

        int totalCount = await PersonData.FindAllAsync(
            offset,
            page.Size,
            (
                personId,
                nationalNo,
                firstName,
                secondName,
                thirdName,
                lastName,
                gender,
                dateOfBirth,
                nationality,
                phoneNumber,
                email
            ) => people.Add(new PersonSummary(
                personId,
                nationalNo,
                firstName,
                secondName,
                thirdName,
                lastName,
                Enum.IsDefined(typeof(Gender), (int)gender) ? ((Gender)gender).ToString()
                : throw new InvalidOperationException($"Unknown Gender Value: {gender}"),
                dateOfBirth,
                nationality,
                phoneNumber,
                email
                )));

        return new PagedResult<PersonSummary>(people, totalCount, page.Number, page.Size);
    }
}
