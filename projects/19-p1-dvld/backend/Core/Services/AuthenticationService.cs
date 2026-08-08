using Core.DTOs;
using Data;
namespace Core.Services;

public sealed class AuthenticationService
{
    private readonly IJwtService _jwtService;
    private readonly PasswordHasher _passwordHasher;
    private const int RefreshTokenExpiryDays = 30;

    public AuthenticationService(IJwtService jwtService, PasswordHasher passwordHasher)
    {
        _jwtService = jwtService;
        _passwordHasher = passwordHasher;
    }

    public async Task<AuthResult> LoginAsync(LoginRequest request)
    {

        UserRecord? userRecord = await UserData.GetByUsernameAsync(request.Username);

        if (userRecord == null || !_passwordHasher.Verify(request.Password, userRecord.PasswordHash))
            throw new UnauthorizedAccessException("Invalid credentials.");

        if (!userRecord.IsActive)
            throw new UnauthorizedAccessException("Account is inactive.");

        return await IssueTokenPairAsync(userRecord.UserID, userRecord.UserName, userRecord.IsActive);
    }

    public async Task LogoutAsync(string refreshToken)
    {

        string refreshTokenHash = _passwordHasher.HashToken(refreshToken);
        RefreshTokenRecord? record = await RefreshTokenData.GetActiveByHashAsync(refreshTokenHash);

        if (record == null)
            return; // already loged out


        await RefreshTokenData.RevokeAllByUserIdAsync(record.UserId);
    }

    public async Task<AuthResult> RotateAsync(string refreshToken)
    {

        string refreshTokenHash = _passwordHasher.HashToken(refreshToken);
        RefreshTokenRecord? record = await RefreshTokenData.GetActiveByHashAsync(refreshTokenHash);

        if (record == null)
            throw new UnauthorizedAccessException("Session expired, please login again.");


        await RefreshTokenData.RevokeAsync(record.RefreshTokenId);

        return await IssueTokenPairAsync(record.UserId, record.Username, record.IsActive);

    }

    private async Task<AuthResult> IssueTokenPairAsync(int userId, string username, bool isActive)
    {
        string accessToken = _jwtService.IssueAccessToken(userId, username, isActive);
        string refreshToken = _jwtService.IssueRefreshToken();
        string refreshTokenHash = _passwordHasher.HashToken(refreshToken);

        await RefreshTokenData.CreateAsync(userId, refreshTokenHash, DateTime.UtcNow.AddDays(RefreshTokenExpiryDays));

        return new AuthResult(accessToken, refreshToken);
    }

}
