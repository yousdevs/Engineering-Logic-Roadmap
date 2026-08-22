using Core.DTOs;
using Data;
namespace Core.Services;


public sealed class LicenseClassService
{

    public async Task<IReadOnlyList<LicenseClassSummary>> GetAllAsync()
    {

        var records = await LicenseClassData.FindAllAsync();

        return records.Select(x => new LicenseClassSummary(
                x.Id,
                x.Title,
                x.Description,
                x.MinAge,
                x.ValidityLengthYears,
                x.Fees
            )).ToList();
    }
}
