﻿using Lab3.Entity.Hotel.People;
using Lab3.Entity.Hotel.Rooms;

namespace Lab3.Entity.Hotel.Stays;

public class Staying
{
    public long Id { get; set; }
    public DateTime CheckedInAt { get; set; }
    public DateTime CheckedOutAt { get; set; }

    public required Client Client { get; set; }
    public required Room Room { get; set; }
}