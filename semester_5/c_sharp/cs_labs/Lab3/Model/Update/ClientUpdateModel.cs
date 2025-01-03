﻿using System.ComponentModel.DataAnnotations;
using Lab3.Model.View;
using Newtonsoft.Json;

namespace Lab3.Model.Update;

public class ClientUpdateModel
{
    public required long Id { get; set; }
    [MaxLength(100)] 
    public required string FullName { get; set; }
    [MaxLength(10)] 
    public required string Passport { get; set; }

}