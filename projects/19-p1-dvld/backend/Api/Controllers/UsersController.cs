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
}
