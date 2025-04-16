package ru.mehoil.factory.impl;

import ru.mehoil.data.Ceiling;
import ru.mehoil.data.Device;
import ru.mehoil.data.Floor;
import ru.mehoil.data.Furniture;
import ru.mehoil.data.impl.modern.DecentCeiling;
import ru.mehoil.data.impl.modern.DecentFloor;
import ru.mehoil.data.impl.modern.ModernDevice;
import ru.mehoil.data.impl.modern.ModernFurniture;
import ru.mehoil.factory.RenovationFactory;

public class ModernRenovationFactory extends RenovationFactory {
    @Override
    public Furniture createFurniture() {
        return new ModernFurniture();
    }

    @Override
    public Device createDevice() {
        return new ModernDevice();
    }

    @Override
    public Ceiling createCeiling() {
        return new DecentCeiling();
    }

    @Override
    public Floor createFloor() {
        return new DecentFloor();
    }
}
