using Core.DTOs;
using Core.Entities;
using Data;
namespace Core.Services;

public sealed class UserService
{


    private readonly PasswordHasher _passwordHasher;
    public UserService(PasswordHasher passwordHasher)
    {

        _passwordHasher = passwordHasher;
    }

    public async Task<int> CreateAsync(CreateUserForm form)
    {

        string passwordHash = _passwordHasher.Hash(form.Password);
        var user = User.Create(form.PersonId, form.Username, passwordHash);

        int? userId = await UserData.InsertAsync(
            user.PersonId,
            user.Username,
            user.PasswordHash,
            user.IsActive
            );

        if (userId == null)
            throw new InvalidOperationException("Failed to create user — no ID returned from database.");


        return userId.Value;
    }
}
