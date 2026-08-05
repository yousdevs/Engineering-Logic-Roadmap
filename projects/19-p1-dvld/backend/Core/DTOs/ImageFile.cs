namespace Core.DTOs;

public sealed record ImageFile(Stream Content, string FileName, string ContentType);