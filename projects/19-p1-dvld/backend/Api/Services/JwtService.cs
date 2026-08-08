using Core;
using Core.Services;
using Microsoft.IdentityModel.Tokens;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Security.Cryptography;

namespace Api.Services;

public sealed class JwtService : IJwtService
{

    private readonly string _secret;
    private readonly string _issuer;
    private readonly string _audience;
    private readonly int _accessTokenExpiryMinutes;


    public JwtService(string secret, string issuer, string audience, int accessTokenExpiryMinutes)
    {
        _secret = secret;
        _issuer = issuer;
        _audience = audience;
        _accessTokenExpiryMinutes = accessTokenExpiryMinutes;
    }

    public string IssueAccessToken(int userId, string username, bool isActive)
    {
        var key = new SymmetricSecurityKey(Convert.FromBase64String(_secret));
        var credentials = new SigningCredentials(key, SecurityAlgorithms.HmacSha256);

        var claims = new[]
        {
            new Claim(JwtRegisteredClaimNames.Sub, userId.ToString()),
            new Claim(JwtRegisteredClaimNames.UniqueName, username),
            new Claim("isActive", isActive.ToString()),
            new Claim(JwtRegisteredClaimNames.Jti, Guid.NewGuid().ToString())
        };

        var token = new JwtSecurityToken(
            issuer: _issuer,
            audience: _audience,
            claims: claims,
            expires: DateTime.UtcNow.AddMinutes(_accessTokenExpiryMinutes),
            signingCredentials: credentials
            );

        return new JwtSecurityTokenHandler().WriteToken(token);
    }

    public string IssueRefreshToken()
    {
        return Convert.ToBase64String(RandomNumberGenerator.GetBytes(64));
    }

    public AccessTokenClaims? ValidateAccessToken(string token)
    {
        var key = new SymmetricSecurityKey(Convert.FromBase64String(_secret));

        var parameters = new TokenValidationParameters
        {
            ValidateIssuer = true,
            ValidIssuer = _issuer,
            ValidateAudience = true,
            ValidAudience = _audience,
            ValidateIssuerSigningKey = true,
            IssuerSigningKey = key,
            ValidateLifetime = true,
            ClockSkew = TimeSpan.Zero
        };

        try
        {
            var principal = new JwtSecurityTokenHandler()
                .ValidateToken(token, parameters, out _);

            var sub = principal.FindFirst(JwtRegisteredClaimNames.Sub)?.Value;
            var username = principal.FindFirst(JwtRegisteredClaimNames.UniqueName)?.Value;
            var isActive = principal.FindFirst("isActive")?.Value;

            if (sub is null || username is null || isActive is null)
                return null;

            return new AccessTokenClaims(int.Parse(sub), username, bool.Parse(isActive));
        }
        catch
        {
            return null;
        }
    }
}
