using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
namespace Api.Controllers;

[Authorize]
[Route("api/application-types")]
[ApiController]
public sealed class ApplicationTypesController : ControllerBase
{

    private readonly ApplicationTypesService _applicationTypesService;

    public ApplicationTypesController(ApplicationTypesService applicationTypesService)
    {
        _applicationTypesService = applicationTypesService;
    }

    [HttpGet]
    public async Task<ActionResult<ApplicationTypesList>> GetAllAsync()
    {
        var res = await _applicationTypesService.GetAllAsync();
        return Ok(res);
    }

    [HttpGet("{id:int}")]
    public async Task<ActionResult<ApplicationTypeDetails>> GetByIdAsync(int id)
    {
        var res = await _applicationTypesService.GetByIdAsync(id);
        return Ok(res);
    }

    [HttpPatch("{id:int}")]
    public async Task<IActionResult> UpdateAsync(int id, [FromBody] UpdateApplicationTypeRequest request)
    {
        await _applicationTypesService.UpdateAsync(id, request);

        return NoContent();
    }
}
