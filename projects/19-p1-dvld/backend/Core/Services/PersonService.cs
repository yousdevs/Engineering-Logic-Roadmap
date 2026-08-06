namespace Core.Services;

using Core.DTOs;
using Core.Entities;
using Data;
public sealed class PersonService
{

    private readonly ImageStorageService _imageStorageService;

    public PersonService(ImageStorageService imageStorageService)
    {
        _imageStorageService = imageStorageService;
    }

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

    public async Task<int> CreateAsync(PersonForm form)
    {

        if (!Enum.TryParse<Gender>(form.Gender, out var gender))
            throw new ArgumentException($"Invalid gender: {form.Gender}.");

        if (form.NationalityCountryId < 1 || form.NationalityCountryId > short.MaxValue)
            throw new ArgumentException("Invalid country.");

        short nationalityCountryId = (short)form.NationalityCountryId;

        var person = Person.Create(
            form.FirstName,
            form.SecondName,
            form.ThirdName,
            form.LastName,
            gender,
            form.DateOfBirth,
            form.NationalNo,
            nationalityCountryId,
            form.Address,
            form.PhoneNumber,
            form.Email
            );

        int id = await PersonData.InsertAsync(
            person.NationalNo,
            person.FirstName,
            person.SecondName,
            person.ThirdName,
            person.LastName,
            person.DateOfBirth,
            (byte)person.Gender,
            person.Address,
            person.PhoneNumber,
            person.Email,
            person.NationalityCountryId
            );

        return id;
    }

    public async Task<string> SetPersonImageAsync(int id, ImageFile file)
    {

        PersonRecord? record = await PersonData.GetByIdAsync(id);

        if (record is null)
            throw new ArgumentException($"Person with id={id} does not exist.");

        var person = Person.Reconstitute(
            record.PersonID,
            record.FirstName,
            record.SecondName,
            record.ThirdName,
            record.LastName,
            (Gender)record.Gendor,
            record.DateOfBirth,
            record.NationalNo,
            (short)record.NationalityCountryID,
            record.Address,
            record.Phone,
            record.Email,
            record.ImagePath
            );

        string path = await _imageStorageService.SaveAsync(file);
        string? oldPath = person.ImagePath;

        try
        {
            person.ChangeImage(path);
            await PersonData.UpdateAsync(new PersonRecord(
                person.Id,
                person.NationalNo,
                person.FirstName,
                person.SecondName,
                person.ThirdName,
                person.LastName,
                person.DateOfBirth,
                (byte)person.Gender,
                person.Address,
                person.PhoneNumber,
                person.Email,
                person.NationalityCountryId,
                person.ImagePath
            ));

        }
        catch
        {
            _imageStorageService.Delete(path);
            throw;
        }

        _imageStorageService.Delete(oldPath);


        return _imageStorageService.BuildUrl(path);
    }

    public async Task RemovePersonImageAsync(int id)
    {
        PersonRecord? record = await PersonData.GetByIdAsync(id);

        if (record is null)
            throw new ArgumentException($"Person with id={id} does not exist.");

        var person = Person.Reconstitute(
            record.PersonID,
            record.FirstName,
            record.SecondName,
            record.ThirdName,
            record.LastName,
            (Gender)record.Gendor,
            record.DateOfBirth,
            record.NationalNo,
            (short)record.NationalityCountryID,
            record.Address,
            record.Phone,
            record.Email,
            record.ImagePath
            );

        string? oldPath = person.ImagePath;
        if (oldPath == null)
            return;

        person.RemoveImage();
        await PersonData.UpdateAsync(new PersonRecord(
            person.Id,
            person.NationalNo,
            person.FirstName,
            person.SecondName,
            person.ThirdName,
            person.LastName,
            person.DateOfBirth,
            (byte)person.Gender,
            person.Address,
            person.PhoneNumber,
            person.Email,
            person.NationalityCountryId,
            person.ImagePath
            ));
        _imageStorageService.Delete(oldPath);

    }


    public async Task<bool> ExistsByNationalNoAsync(string nationalNo) => await PersonData.ExistsByNationalNoAsync(nationalNo);

    public async Task<bool> ExistsByPhoneNumberAsync(string phoneNumber) => await PersonData.ExistsByPhoneNumberAsync(phoneNumber);

    public async Task<bool> ExistsByEmailAsync(string email) => await PersonData.ExistsByEmailAsync(email);
}
