using Core.DTOs;
using Core.Entities;
using Data;
namespace Core.Services;

public sealed class UserService
{


    private readonly PasswordHasher _passwordHasher;
    private readonly ICurrentUser _currentUser;
    public UserService(PasswordHasher passwordHasher, ICurrentUser currentUser)
    {

        _passwordHasher = passwordHasher;
        _currentUser = currentUser;
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

    public async Task SuspendAsync(int userId)
    {

        if (userId == _currentUser.UserId)
            throw new InvalidOperationException("Cannot suspend your own account.");

        var userRecord = await UserData.FindByIdAsync(userId);

        if (userRecord == null)
            throw new KeyNotFoundException($"User with UserId = {userId} does not exist.");

        var user = User.Reconstitute(
            userRecord.UserID,
            userRecord.PersonID,
            userRecord.UserName,
            userRecord.PasswordHash,
            userRecord.IsActive
            );

        user.Deactivate();

        bool updated = await UserData.UpdateAsync(
            new UserRecord(
                user.Id,
                user.PersonId,
                user.Username,
                user.PasswordHash,
                user.IsActive
                )
            );

        if (!updated)
            throw new KeyNotFoundException($"User with UserId = {userId} does not exist.");

        await RefreshTokenData.RevokeAllByUserIdAsync(userId);
    }


    public async Task ActivateAsync(int userId)
    {


        var userRecord = await UserData.FindByIdAsync(userId);

        if (userRecord == null)
            throw new KeyNotFoundException($"User with UserId = {userId} does not exist.");

        var user = User.Reconstitute(

                userRecord.UserID,
                userRecord.PersonID,
                userRecord.UserName,
                userRecord.PasswordHash,
                userRecord.IsActive
            );

        user.Activate();

        bool updated = await UserData.UpdateAsync(
            new UserRecord(
                user.Id,
                user.PersonId,
                user.Username,
                user.PasswordHash,
                user.IsActive
                )
            );

        if (!updated)
            throw new KeyNotFoundException($"User with UserId = {userId} does not exist.");
    }
}
