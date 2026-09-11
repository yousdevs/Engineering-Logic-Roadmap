using Xunit;
using DSA.Core.Problems.QueuesAndStacks;

namespace DSA.Tests.Problems.QueuesAndStacks;

public class BrowserBackButtonTests
{
    [Fact]
    public void GoBack_ReturnsUrlInReverseOrder()
    {
        // Given
        var browser = new BrowserBackButton();
        browser.Visit("google.com");
        browser.Visit("github.com");
    
        Assert.Equal("github.com", browser.GoBack());
        Assert.Equal("google.com", browser.GoBack());
    }

    [Fact]
    public void GoBack_WhenNoHistory_ReturnsNoHistory()
    {
        var browser = new BrowserBackButton();
        Assert.Equal("No history", browser.GoBack());
    }
}