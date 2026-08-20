using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers;

[Authorize]
[Route("api/licenses")]
[ApiController]
public sealed class LicensesController : ControllerBase
{

    private readonly LicenseService _licenseService;
    public LicensesController(LicenseService licenseService)
    {
        _licenseService = licenseService;
    }

    [HttpPost("local")]
    public async Task<IActionResult> IssueLocalDrivingLicenseAsync([FromBody] IssueLocalDrivingLicenseRequest request)
    {

        var licenseId = await _licenseService.IssueLocalDrivingLicenseAsync(request.ApplicationId, request.Notes);

        return Created(
            $"/api/licenses/local/{licenseId}",
            new { licenseId }
            );
    }

    [HttpPost("international")]
    public async Task<IActionResult> IssueInternationalLicenseAsync([FromBody] IssueInternationalLicenseRequest request)
    {

        var licenseId = await _licenseService.IssueInternationalLicenseAsync(request.LocalLicenseId);

        return Created(
            $"/api/licenses/international/{licenseId}",
            new { InternationalLicenseId = licenseId }
            );
    }

    [HttpPost("local/{licenseId:int}/renewals")]
    public async Task<IActionResult> RenewLocalLicenseAsync(int licenseId, [FromBody] RenewLocalLicenseRequest request)
    {

        var newLocalLicenseId = await _licenseService.RenewLocalLicenseAsync(licenseId, request.Notes);

        return Created(
            $"/api/licenses/local/{newLocalLicenseId}",
            new { LocalLicenseId = newLocalLicenseId }
            );
    }

    [HttpPost("local/{licenseId:int}/damaged-replacement")]
    public async Task<IActionResult> ReplaceDamagedLicenseAsync(int licenseId, [FromBody] ReplaceDamagedLicenseRequest request)
    {

        var newLocalLicenseId = await _licenseService.ReplaceDamagedLocalLicenseAsync(licenseId, request.Notes);

        return Created(
            $"/api/licenses/local/{newLocalLicenseId}",
            new { localLicenseId = newLocalLicenseId }
            );
    }

    [HttpPost("local/{licenseId:int}/lost-replacement")]
    public async Task<IActionResult> ReplaceLostLicenseAsync(int licenseId, [FromBody] ReplaceLostLicenseRequest request)
    {

        var newLocalLicenseId = await _licenseService.ReplaceLostLocalLicenseAsync(licenseId, request.Notes);

        return Created(
            $"/api/licenses/local/{newLocalLicenseId}",
            new { localLicenseId = newLocalLicenseId }
            );
    }
}
