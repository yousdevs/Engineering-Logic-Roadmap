
namespace Core.DTOs;

public sealed record ApplicationTypeSummary(

    int Id,
    string Title,
    decimal Fee
    );

public sealed record ApplicationTypesList(

    IReadOnlyList<ApplicationTypeSummary> Items
    );

public sealed record ApplicationTypeDetails(

    int Id,
    string Title,
    decimal Fee
    );

public sealed record UpdateApplicationTypeRequest(

    string Title,
    decimal Fee

    );