namespace Core;

public static class Guard
{

    public static void RequireNonEmptyIfProvided(string? value, string fieldName, string context)
    {
        if (value is null) return;
        if (value == String.Empty)
        {
            throw new ArgumentException(context + ": " + fieldName + " cannot be empty.");
        }
    }
    public static void RequireNonEmpty(string value, string fieldName, string context)
    {
        if (value == String.Empty)
        {
            throw new ArgumentException(context + ": " + fieldName + " cannot be empty.");
        }
    }

    public static void RequireMinLength(string value, int min, string fieldName, string context)
    {
        if (value.Length < min)
        {
            throw new ArgumentException(context + ": " + fieldName + " min length must be equal or greater than " + min + ".");
        }
    }

    public static void RequireMaxLength(string value, int max, string fieldName, string context)
    {
        if (value.Length > max)
        {
            throw new ArgumentException(context + ": " + fieldName + " max length must be less than " + max + ".");
        }
    }

    public static void RequireMinAge(DateTime value, int minAge, string fieldName, string context)
    {


        if (value > DateTime.Today.AddYears(-minAge))
        {
            throw new ArgumentException(context + ": " + fieldName + " min age must be " + minAge + "y.");
        }
    }

    public static void RequireIntegerInRange(int value, int min, int max, string fieldName, string context)
    {
        if (value < min || value > max)
        {
            throw new ArgumentException(context + ": " + fieldName + " must be in range (" + min + "-" + max + ").");
        }
    }

}
