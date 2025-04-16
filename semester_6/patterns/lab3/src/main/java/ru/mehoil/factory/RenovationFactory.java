package ru.mehoil.factory;

import ru.mehoil.data.Ceiling;
import ru.mehoil.data.Device;
import ru.mehoil.data.Floor;
import ru.mehoil.data.Furniture;

public abstract class RenovationFactory {
    public abstract Furniture createFurniture();

    public abstract Device createDevice();

    public abstract Ceiling createCeiling();

    public abstract Floor createFloor();
}
