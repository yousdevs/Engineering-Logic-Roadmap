namespace Core.Entities;

public sealed class User
{
    public int Id { get; internal set; }
    public int PersonId { get; private set; }
    public string Username { get; private set; }
    public string PasswordHash { get; private set; }
    public bool IsActive { get; private set; }


    private User(int id, int personId, string username, string passwordHash, bool isActive)
    {
        Id = id;
        PersonId = personId;
        Username = username;
        PasswordHash = passwordHash;
        IsActive = isActive;
    }

    public static User Create(int personId, string username, string passwordHash)
    {
        Guard.RequireNonEmpty(username, nameof(username), "User::Create");
        Guard.RequireMinLength(username, 3, nameof(username), "User::Create");

        return new User(-1, personId, username, passwordHash, true);
    }

    public static User Reconstitute(int id, int personId, string username, string passwordHash, bool isActive)
    {
        return new User(id, personId, username, passwordHash, isActive);
    }

    public void ChangeUsername(string newUsername)
    {

        Guard.RequireMinLength(newUsername, 3, nameof(newUsername), "User::ChangeUsername");
        Username = newUsername;
    }
    public void ChangePasswordHash(string newPasswordHash)
    {
        Guard.RequireNonEmpty(newPasswordHash, nameof(newPasswordHash), "User::ChangePasswordHash");
        PasswordHash = newPasswordHash;
    }

    public void Deactivate()
    {
        if (!IsActive)
            return;
        IsActive = false;
    }

    public void Activate()
    {
        if (IsActive)
            return;
        IsActive = true;
    }
}
