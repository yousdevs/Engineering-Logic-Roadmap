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

    public int UserId => int.Parse(User.FindFirst(JwtRegisteredClaimNames.Sub)!.Value);

    public string Username => User.FindFirst(JwtRegisteredClaimNames.UniqueName)!.Value;

    public bool IsActive => bool.Parse(User.FindFirst("isActive")!.Value);
}
