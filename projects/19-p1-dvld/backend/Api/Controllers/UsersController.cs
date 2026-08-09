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
}
