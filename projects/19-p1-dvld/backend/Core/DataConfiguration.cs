using Data;

namespace Core;

public static class DataConfiguration
{

    public static void Initialize(string connectionString)
    {
        PersonData.Initialize(connectionString);
        UserData.Initialize(connectionString);
    }
}
