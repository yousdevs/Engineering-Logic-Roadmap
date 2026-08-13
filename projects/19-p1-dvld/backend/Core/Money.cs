namespace Core;

public readonly record struct Money
{
    public decimal Amount { get; }

    private Money(decimal amount)
    {
        if (amount < 0)
        {
            throw new ArgumentOutOfRangeException(
                nameof(amount),
                amount,
                "Money cannot be negative.");
        }

        if (decimal.Round(amount, 2) != amount)
        {
            throw new ArgumentException(
                "Money cannot have more than two decimal places.",
                nameof(amount));
        }

        Amount = amount;
    }

    public static Money From(decimal amount) => new(amount);

    public static Money Zero => new(0m);

    public static Money operator +(Money left, Money right) => new(left.Amount + right.Amount);
}