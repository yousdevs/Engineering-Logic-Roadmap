namespace Core.Services;

public interface IJwtService
{
    string IssueAccessToken(int userId, string username, bool isActive);

    string IssueRefreshToken();

    int? ValidateAccessToken(string token); // returns userid on success
}
