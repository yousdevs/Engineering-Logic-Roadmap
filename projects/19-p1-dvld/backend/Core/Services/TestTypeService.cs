using Core.DTOs;
using Core.Entities;
using Data;

namespace Core.Services;

public sealed class TestTypeService
{

    public async Task<TestTypeList> GetAllAsync()
    {
        var testTypeRecords = await TestTypeData.FindAllAsync();

        var items = new List<TestTypeSummary>();

        foreach (var item in testTypeRecords)
        {
            items.Add(
                    new TestTypeSummary(item.Id, item.Title, item.Description, item.Fee)
                );
        }

        return new TestTypeList(
                items
            );
    }

    public async Task<TestTypeDetails> GetByIdAsync(int id)
    {

        var record = await TestTypeData.FindByIdAsync(id);

        if (record == null)
            throw new KeyNotFoundException($"TestType with id={id} does not exist.");

        return new TestTypeDetails(
            record.Id,
            record.Title,
            record.Description,
            record.Fee
            );
    }

    public async Task UpdateAsync(int id, UpdateTestTypeRequest request)
    {

        var record = await TestTypeData.FindByIdAsync(id);

        if (record == null)
            throw new KeyNotFoundException($"TestType with id={id} does not exist.");


        var testType = TestType.Reconstitute(
            record.Id,
            record.Title,
            record.Description,
            Money.From(record.Fee)
            );

        testType.ChangeFee(Money.From(request.Fee));
        testType.ChangeTitle(request.Title);
        testType.ChangeDescription(request.Description);

        bool updated = await TestTypeData.UpdateAsync(
            new TestTypeRecord(
                testType.Id,
                testType.Title,
                testType.Description,
                testType.Fee.Amount
                )
            );

        if (!updated)
            throw new KeyNotFoundException($"TestType with id={id} does not exist.");
    }
}
