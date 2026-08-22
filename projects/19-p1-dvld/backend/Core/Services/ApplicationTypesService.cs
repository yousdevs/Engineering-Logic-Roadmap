using Core.DTOs;
using Core.Entities;
using Data;

namespace Core.Services;

public sealed class ApplicationTypesService
{

    public async Task<ApplicationTypesList> GetAllAsync()
    {
        var applicationTypesRecords = await ApplicationTypesData.FindAllAsync();

        var items = new List<ApplicationTypeSummary>();

        foreach (var item in applicationTypesRecords)
        {
            items.Add(
                    new ApplicationTypeSummary(item.Id, item.Title, item.Fee)
                );
        }

        return new ApplicationTypesList(
                items
            );
    }

    public async Task<ApplicationTypeDetails> GetByIdAsync(int id)
    {

        var record = await ApplicationTypesData.FindByIdAsync(id);

        if (record == null)
            throw new KeyNotFoundException($"ApplicationType with id={id} does not exist.");

        return new ApplicationTypeDetails(
            record.Id,
            record.Title,
            record.Fee
            );
    }

    public async Task UpdateAsync(int id, UpdateApplicationTypeRequest request)
    {

        var record = await ApplicationTypesData.FindByIdAsync(id);

        if (record == null)
            throw new KeyNotFoundException($"ApplicationType with id={id} does not exist.");


        var applicationType = ApplicationType.Reconstitute(
            (ApplicationTypeId)record.Id,
            record.Title,
            Money.From(record.Fee)
            );

        applicationType.ChangeFee(Money.From(request.Fee));
        applicationType.ChangeTitle(request.Title);

        bool updated = await ApplicationTypesData.UpdateAsync(
            new ApplicationTypeRecord(
                (int)applicationType.Id,
                applicationType.Title,
                applicationType.Fee.Amount
                )
            );

        if (!updated)
            throw new KeyNotFoundException($"ApplicationType with id={id} does not exist.");
    }
}
