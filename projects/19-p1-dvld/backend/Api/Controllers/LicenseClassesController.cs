using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers;

[Authorize]
[Route("api/license-classes")]
[ApiController]
public sealed class LicenseClassesController : ControllerBase
{

    private readonly LicenseClassService _licenseClassService;

    public LicenseClassesController(LicenseClassService licenseClassService)
    {
        _licenseClassService = licenseClassService;
    }

    [HttpGet]
    public async Task<ActionResult<IReadOnlyList<LicenseClassSummary>>> GetAllAsync()
    {

        var items = await _licenseClassService.GetAllAsync();

        return Ok(items);
    }
}
