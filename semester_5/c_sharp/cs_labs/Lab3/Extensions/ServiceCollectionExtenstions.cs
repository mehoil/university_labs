﻿using Lab3.Repository;
using Lab3.Service;
using Lab3.Service.Impl;

namespace Lab3.Extensions;

public static class ServiceCollectionExtensions
{
    public static IServiceCollection AddServices(this IServiceCollection services)
    {
        services.AddScoped(typeof(IGeneralRepository<>), typeof(GeneralRepository<>));
        services.AddScoped<IHotelService, HotelService>();
        services.AddScoped<IOwnerService, OwnerService>();
        services.AddScoped<IHotelOfferingService, HotelOfferingService>();
        services.AddScoped<IClientService, ClientService>();

        return services;
    }
}