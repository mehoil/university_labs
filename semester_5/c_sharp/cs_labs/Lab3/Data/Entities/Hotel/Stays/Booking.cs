﻿using Lab3.Data.Entities.Hotel.Rooms;
using Lab3.Entities.Enums;
using Lab3.Entities.Hotel.People;

namespace Lab3.Data.Entities.Hotel.Stays;

public class Booking
{
    public long Id { get; set; }
    public required Client Client { get; set; }

    public DateTime CheckingInAt { get; set; }
    public DateTime CheckingOutAt { get; set; }

    public List<RoomClass>? PreferredRoomClasses { get; set; }
    public List<RoomSize>? PreferredRoomSizes { get; set; }
    public List<RoomFeature>? PreferredRoomFeatures { get; set; }
}