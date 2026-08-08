namespace Core.DTOs;

public sealed record LoginRequest(string Username, string Password);
public sealed record AuthResult(string AccessToken, string RefreshToken);

public sealed record RotateRequest(string RefreshToken);