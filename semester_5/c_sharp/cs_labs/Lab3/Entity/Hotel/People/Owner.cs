﻿using System.ComponentModel.DataAnnotations.Schema;

namespace Lab3.Entity.Hotel.People;

public class Owner
{
    public long Id { get; set; }
    public required string FullName { get; set; }

    //  Hotels-to-Owner (Many-to-One)
    public ICollection<Hotel>? Hotels { get; set; } = new List<Hotel>();
}