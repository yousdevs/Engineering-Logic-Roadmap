using Core;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;

namespace Api.Services;

public class CurrentUser : ICurrentUser
{

    private readonly IHttpContextAccessor _accessor;

    public CurrentUser(IHttpContextAccessor accessor)
    {
        _accessor = accessor;
    }

    private ClaimsPrincipal User => _accessor.HttpContext!.User;

    public int UserId
    {
        get
        {
            var claims = User.Claims.Select(c => $"{c.Type}={c.Value}").ToList();
            Console.WriteLine($"Claims: {string.Join(", ", claims)}");

            var value = User.FindFirst(JwtRegisteredClaimNames.Sub)?.Value;
            if (value is null)
                throw new InvalidOperationException("UserId claim not found. Is the user authenticated?");
            return int.Parse(value);
        }
    }

    public string Username => User.FindFirst(JwtRegisteredClaimNames.UniqueName)!.Value;

    public bool IsActive => bool.Parse(User.FindFirst("isActive")!.Value);
}
