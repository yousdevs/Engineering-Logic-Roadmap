using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers;

[Authorize]
[Route("api/[controller]")]
[ApiController]
public sealed class UsersController : ControllerBase
{

    private readonly UserService _userService;

    public UsersController(UserService userService)
    {
        _userService = userService;
    }

    [HttpPost]
    public async Task<ActionResult<int>> CreateAsync([FromBody] CreateUserForm form)
    {

        var userId = await _userService.CreateAsync(form);

        return Created($"/api/users/{userId}", userId);
    }

    [HttpGet]
    public async Task<ActionResult<PagedResult<UserSummary>>> GetAllAsync([FromQuery] int page = 1, [FromQuery] int size = 10)
    {

        var res = await _userService.GetAllAsync(new Page(page, size));

        return Ok(res);
    }

    [HttpPatch("{id:int}/suspend")]
    public async Task<IActionResult> SuspendAsync(int id)
    {
        await _userService.SuspendAsync(id);

        return NoContent();
    }

    [HttpPatch("{id:int}/activate")]
    public async Task<IActionResult> ActivateAsync(int id)
    {
        await _userService.ActivateAsync(id);

        return NoContent();
    }

    [HttpPut("{id:int}/password")]
    public async Task<IActionResult> ForceResetPasswordAsync(int id, [FromBody] ForceResetPasswordRequest request)
    {
        await _userService.ForceResetPasswordAsync(id, request.NewPassword);

        return NoContent();
    }

    [HttpPut("{id:int}/username")]
    public async Task<IActionResult> UpdateUsernameAsync(int id, [FromBody] UpdateUsernameRequest request)
    {
        await _userService.UpdateUsernameAsync(id, request.NewUsername);

        return NoContent();
    }

    [HttpDelete("{id:int}/sessions")]
    public async Task<IActionResult> RevokeAllSessionsAsync(int id)
    {
        await _userService.RevokeAllSessionsAsync(id);

        return NoContent();
    }
}
