using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
namespace Api.Controllers;

[Authorize]
[Route("api/test-types")]
[ApiController]
public sealed class TestTypeController : ControllerBase
{

    private readonly TestTypeService _testTypeService;

    public TestTypeController(TestTypeService testTypeService)
    {
        _testTypeService = testTypeService;
    }

    [HttpGet]
    public async Task<ActionResult<TestTypeList>> GetAllAsync()
    {
        var res = await _testTypeService.GetAllAsync();
        return Ok(res);
    }

    [HttpGet("{id:int}")]
    public async Task<ActionResult<TestTypeDetails>> GetByIdAsync(int id)
    {
        var res = await _testTypeService.GetByIdAsync(id);
        return Ok(res);
    }

    [HttpPatch("{id:int}")]
    public async Task<IActionResult> UpdateAsync(int id, [FromBody] UpdateTestTypeRequest request)
    {
        await _testTypeService.UpdateAsync(id, request);

        return NoContent();
    }
}
