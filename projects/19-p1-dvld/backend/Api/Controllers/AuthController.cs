using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers;

[Route("api/[controller]")]
[ApiController]
public sealed class AuthController : ControllerBase
{

    private readonly AuthenticationService _authenticationService;

    public AuthController(AuthenticationService authenticationService)
    {
        _authenticationService = authenticationService;
    }

    [HttpPost("login")]
    public async Task<IActionResult> Login([FromBody] LoginRequest request)
    {
        var res = await _authenticationService.LoginAsync(request);
        Response.Cookies.Append("refreshToken", res.RefreshToken, RefreshTokenCookieOptions());

        return Ok(new { res.AccessToken });
    }

    [HttpPost("logout")]
    public async Task<IActionResult> Logout()
    {
        var refreshToken = Request.Cookies["refreshToken"];

        if (refreshToken is null)
            return NoContent();

        await _authenticationService.LogoutAsync(refreshToken);

        Response.Cookies.Delete("refreshToken");

        return NoContent();
    }

    [HttpPost("refresh")]
    public async Task<IActionResult> Rotate()
    {

        var refreshToken = Request.Cookies["refreshToken"];

        if (refreshToken is null)
            throw new UnauthorizedAccessException("Session expired, login again.");


        AuthResult res = await _authenticationService.RotateAsync(refreshToken);

        Response.Cookies.Append("refreshToken", res.RefreshToken, RefreshTokenCookieOptions());

        return Ok(new { res.AccessToken });
    }

    private static CookieOptions RefreshTokenCookieOptions() => new()
    {
        HttpOnly = true,
        Secure = true,
        SameSite = SameSiteMode.None,
        Expires = DateTimeOffset.UtcNow.AddDays(30)
    };
}
