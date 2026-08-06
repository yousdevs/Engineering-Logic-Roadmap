using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers;


[Route("api/[controller]")]
[ApiController]
public class PeopleController : ControllerBase
{

    private readonly PersonService _personService;

    public PeopleController(PersonService personService)
    {

        _personService = personService;
    }

    [HttpGet]
    [ProducesResponseType(typeof(PagedResult<PersonSummary>), StatusCodes.Status200OK)]
    [ProducesResponseType(typeof(ErrorResponse), StatusCodes.Status400BadRequest)]
    [ProducesResponseType(typeof(ErrorResponse), StatusCodes.Status500InternalServerError)]
    public async Task<ActionResult<PagedResult<PersonSummary>>> GetAll([FromQuery] int page = 1, [FromQuery] int pageSize = 10)
    {

        var result = await _personService.GetAllAsync(new Page(page, pageSize));

        return Ok(result);
    }

    [HttpPost]
    public async Task<ActionResult<int>> Create([FromBody] PersonForm form)
    {

        int id = await _personService.CreateAsync(form);

        //return CreatedAtAction(nameof(GetById), new { id}, id);
        return StatusCode(StatusCodes.Status201Created, id);
    }

    [HttpPut("{id:int}/image")]
    public async Task<IActionResult> SetImage(int id, [FromForm] IFormFile image)
    {

        if (image is null)
            return BadRequest("Image file is required.");

        string imageUrl = await _personService.SetPersonImageAsync(id,
            new ImageFile(image.OpenReadStream(), image.FileName, image.ContentType));

        return Ok(new { imageUrl });
    }

    [HttpDelete("{id:int}/image")]
    public async Task<IActionResult> DeleteImage(int id)
    {

        await _personService.RemovePersonImageAsync(id);

        return NoContent();
    }

    [HttpGet("exists")]
    public async Task<IActionResult> Exist([FromQuery] string? nationalNo, [FromQuery] string? email, [FromQuery] string? phoneNumber)
    {

        var filtersProvided = new[] { nationalNo, email, phoneNumber }.Count(f => f != null);

        if (filtersProvided != 1)
            return BadRequest("Exactly one filter must be provided.");

        bool exists =
            nationalNo != null ? await _personService.ExistsByNationalNoAsync(nationalNo)
            : email != null ? await _personService.ExistsByEmailAsync(email)
            : await _personService.ExistsByPhoneNumberAsync(phoneNumber!);

        return Ok(new { exists });
    }

    [HttpPut("{id:int}")]
    public async Task<IActionResult> Update(int id, [FromBody] PersonForm form)
    {
        await _personService.UpdateAsync(id, form);

        return NoContent();
    }

    [HttpGet("{id:int}")]
    public async Task<ActionResult<PersonDetails>> GetFullDetails(int id)
    {

        var details = await _personService.GetDetailsByIdAsync(id);

        return Ok(details);
    }

    [HttpDelete("{id:int}")]
    public async Task<IActionResult> Delete(int id)
    {

        await _personService.DeleteAsync(id);

        return NoContent();
    }

}
