using Core.DTOs;
using Core.Entities;
using Data;
namespace Core.Services;

public sealed class AuthenticationService
{
    private readonly IJwtService _jwtService;
    private readonly PasswordHasher _passwordHasher;
    private readonly ICurrentUser _currentUser;
    private const int RefreshTokenExpiryDays = 30;

    public AuthenticationService(IJwtService jwtService, PasswordHasher passwordHasher, ICurrentUser currentUser)
    {
        _jwtService = jwtService;
        _passwordHasher = passwordHasher;
        _currentUser = currentUser;
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


    public async Task ChangePasswordAsync(ChangePasswordRequest request)
    {


        var userRecord = await UserData.FindByIdAsync(_currentUser.UserId);

        if (userRecord == null)
            throw new KeyNotFoundException($"User with UserId={_currentUser.UserId} not found.");

        if (!_passwordHasher.Verify(request.CurrentPassword, userRecord.PasswordHash))
            throw new UnauthorizedAccessException("Invalid credentials.");

        var user = User.Reconstitute(
            userRecord.UserID,
            userRecord.PersonID,
            userRecord.UserName,
            userRecord.PasswordHash,
            userRecord.IsActive
            );

        user.ChangePasswordHash(_passwordHasher.Hash(request.NewPassword));

        bool updated = await UserData.UpdateAsync(new UserRecord(
                user.Id,
                user.PersonId,
                user.Username,
                user.PasswordHash,
                user.IsActive
            ));

        if (!updated)
            throw new KeyNotFoundException("Failed to update password — user may have been deleted.");

        await RefreshTokenData.RevokeAllByUserIdAsync(_currentUser.UserId);
    }
}
