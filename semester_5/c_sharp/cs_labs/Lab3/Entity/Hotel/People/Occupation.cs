﻿using Lab3.Entity.Enums;

namespace Lab3.Entity.Hotel.People;

public class Occupation
{
    public long Id { get; set; }
    public long Salary { get; set; }

    public OccupationType Type { get; set; }
}