
namespace Core.DTOs;

public sealed record TestTypeSummary(

    int Id,
    string Title,
    string Description,
    decimal Fee
    );

public sealed record TestTypeList(

    IReadOnlyList<TestTypeSummary> Items
    );

public sealed record TestTypeDetails(

    int Id,
    string Title,
    string Description,
    decimal Fee
    );

public sealed record UpdateTestTypeRequest(

    string Title,
    string Description,
    decimal Fee

    );