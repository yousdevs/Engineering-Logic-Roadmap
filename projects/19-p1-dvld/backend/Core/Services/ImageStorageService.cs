using Core.DTOs;
namespace Core.Services;

public sealed class ImageStorageService
{

    private readonly string _storagePath;
    private readonly string _baseUrl;

    public ImageStorageService(string storagePath, string baseUrl)
    {
        _storagePath = storagePath;
        _baseUrl = baseUrl;
    }

    public async Task<string> SaveAsync(ImageFile file)
    {

        string fileName = $"{Guid.NewGuid()}{Path.GetExtension(file.FileName)}";
        string fullPath = Path.Combine(_storagePath, fileName);

        await using var stream = File.OpenWrite(fullPath);
        await file.Content.CopyToAsync(stream);

        return fileName;
    }

    public void Delete(string? imagePath)
    {
        if (imagePath == null) return;

        string fullPath = Path.Combine(_storagePath, imagePath);

        if (File.Exists(fullPath))
            File.Delete(fullPath);
    }

    public string BuildUrl(string fileName) => $"{_baseUrl}{fileName}";

}
