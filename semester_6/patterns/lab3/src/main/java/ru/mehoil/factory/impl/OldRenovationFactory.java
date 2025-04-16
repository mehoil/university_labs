package ru.mehoil.factory.impl;

import ru.mehoil.data.Ceiling;
import ru.mehoil.data.Device;
import ru.mehoil.data.Floor;
import ru.mehoil.data.Furniture;
import ru.mehoil.data.impl.old.BadCeiling;
import ru.mehoil.data.impl.old.BadFloor;
import ru.mehoil.data.impl.old.OldDevice;
import ru.mehoil.data.impl.old.OldFurniture;
import ru.mehoil.factory.RenovationFactory;

public class OldRenovationFactory extends RenovationFactory {
    @Override
    public Furniture createFurniture() {
        return new OldFurniture();
    }

    @Override
    public Device createDevice() {
        return new OldDevice();
    }

    @Override
    public Ceiling createCeiling() {
        return new BadCeiling();
    }

    @Override
    public Floor createFloor() {
        return new BadFloor();
    }
}
