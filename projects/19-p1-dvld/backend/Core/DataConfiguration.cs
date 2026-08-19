using Data;

namespace Core;

public static class DataConfiguration
{

    public static void Initialize(string connectionString)
    {
        PersonData.Initialize(connectionString);
        UserData.Initialize(connectionString);
        RefreshTokenData.Initialize(connectionString);
        ApplicationTypesData.Initialize(connectionString);
        TestTypeData.Initialize(connectionString);
        LicenseClassData.Initialize(connectionString);
        ApplicationData.Initialize(connectionString);
        LocalDrivingLicenseApplicationData.Initialize(connectionString);
        TestAppointmentData.Initialize(connectionString);
        LicenseData.Initialize(connectionString);
        DriverData.Initialize(connectionString);
    }
}
