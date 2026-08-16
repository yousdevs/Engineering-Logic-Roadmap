using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers;

[Authorize]
[Route("api")]
[ApiController]
public sealed class TestController : ControllerBase
{
    private readonly TestService _testService;

    public TestController(TestService testService)
    {
        _testService = testService;
    }


    [HttpPost("applications/{applicationId:int}/tests")]
    public async Task<IActionResult> ScheduleTest(int applicationId, [FromBody] ScheduleTestRequest request)
    {
        var appointmentId = await _testService.ScheduleTestAsync(applicationId, request.TestTypeId, request.AppointmentDate);

        return Created(
            $"api/test-appointments/{appointmentId}",
            new { id = appointmentId }
            );
    }

    [HttpPost("test-appointments/{appointmentId:int}/result")]
    public async Task<IActionResult> TakeTestAsync(int appointmentId, [FromBody] TakeTestRequest request)
    {

        var testId = await _testService.TakeTestAsync(appointmentId, request.Passed, request.Notes);

        return Created(
            $"/api/tests/{testId}",
            new { id = testId }
            );
    }
}
