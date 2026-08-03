using Microsoft.AspNetCore.Mvc;

namespace Api.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TestController : ControllerBase
    {

        [HttpGet(Name = "GetTest")]
        public string Get()
        {
            return "Test Succeed";
        }
    }
}
