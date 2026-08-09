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

    public async Task<PagedResult<UserSummary>> GetAllAsync(Page page)
    {

        int offset = (page.Number - 1) * page.Size;

        var userPage = await UserData.FindAllAsync(offset, page.Size);

        var items = new List<UserSummary>();

        foreach (var item in userPage.Items)
        {
            items.Add(new UserSummary(
                item.UserId,
                item.FirstName,
                item.LastName,
                item.Username,
                item.IsActive ? "Active" : "Inactive"
                ));
        }

        return new PagedResult<UserSummary>(items, userPage.Total, page.Number, page.Size);

    }
}
