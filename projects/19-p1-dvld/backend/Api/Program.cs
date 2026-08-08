
using Api.Services;
using Core;
using Core.DTOs;
using Core.Services;
using Microsoft.AspNetCore.Diagnostics;
using Microsoft.Extensions.FileProviders;

namespace Api;

public class Program
{
    public static void Main(string[] args)
    {

        var builder = WebApplication.CreateBuilder(args);

        // Add services to the container.

        var jwtConfig = builder.Configuration.GetSection("Jwt");

        builder.Services.AddSingleton<IJwtService>(new JwtService(

            jwtConfig["Secret"]!,
            jwtConfig["Issuer"]!,
            jwtConfig["Audience"]!,
            int.Parse(jwtConfig["AccessTokenExpiryMinutes"]!)
            ));
        builder.Services.AddSingleton<PasswordHasher>();
        builder.Services.AddScoped<AuthenticationService>();

        builder.Services.AddControllers();





        var imageStoragePath = builder.Configuration["ImageStorage:Path"]!;

        Directory.CreateDirectory(imageStoragePath);

        builder.Services.AddSingleton(
            new ImageStorageService(
                imageStoragePath,
                builder.Configuration["ImageStorage:BaseUrl"]!
            ));

        builder.Services.AddScoped<PersonService>();

        // Learn more about configuring OpenAPI at https://aka.ms/aspnet/openapi
        builder.Services.AddOpenApi();

        builder.Services.AddCors(options =>
        {
            options.AddPolicy("Frontend", policy =>
            {
                policy.WithOrigins("http://localhost:5173")
                      .AllowAnyHeader()
                      .AllowAnyMethod();
            });
        });

        var app = builder.Build();

        // Configure the HTTP request pipeline.

        DataConfiguration.Initialize(builder.Configuration.GetConnectionString("Default")!);

        app.UseExceptionHandler(app => app.Run(async context =>
        {
            var exception = context.Features.Get<IExceptionHandlerFeature>()?.Error;

            var (status, message) = exception switch
            {
                ArgumentException ex => (400, ex.Message),
                InvalidOperationException ex => (500, ex.Message),
                _ => (500, "An unexpected error occured.")
            };

            context.Response.StatusCode = status;
            await context.Response.WriteAsJsonAsync(new ErrorResponse(message));
        }));

        if (app.Environment.IsDevelopment())
        {
            app.MapOpenApi();
        }

        app.UseHttpsRedirection();

        app.UseCors("Frontend");

        app.UseAuthorization();

        app.UseStaticFiles(
            new StaticFileOptions
            {
                FileProvider = new PhysicalFileProvider(
                        imageStoragePath
                    ),
                RequestPath = "/images"
            }
            );

        app.MapControllers();



        app.Run();
    }
}
