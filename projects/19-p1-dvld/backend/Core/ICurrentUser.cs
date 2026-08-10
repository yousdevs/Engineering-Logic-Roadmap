namespace Core;

public interface ICurrentUser
{

    int UserId { get; }
    string Username { get; }
    bool IsActive { get; }
}
