using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers;

[Authorize]
[Route("api/[controller]")]
[ApiController]
public class ApplicationsController : ControllerBase
{

    private readonly ApplicationService _applicationService;

    public ApplicationsController(ApplicationService applicationService)
    {
        _applicationService = applicationService;
    }

    [HttpPost]
    public async Task<IActionResult> CreateAsync([FromBody] NewApplicationRequest request)
    {

        int id = await _applicationService.CreateAsync(request);

        return Created($"api/applications/{id}", new { id });
    }


}
