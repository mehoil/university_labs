package ru.mehoil;

import ru.mehoil.factory.RenovationFactory;
import ru.mehoil.factory.impl.ModernRenovationFactory;
import ru.mehoil.factory.impl.OldRenovationFactory;

public class Main {
    public static void main(final String[] args) {
        final RenovationFactory modernFactory = new ModernRenovationFactory();

        final var decentFloor = modernFactory.createFloor();
        final var decentCeiling = modernFactory.createCeiling();
        final var modernDevice = modernFactory.createDevice();
        final var modernFurniture = modernFactory.createFurniture();

        System.out.printf(
                "Modern renovation factory produced: %s || %s || %s || %s%n",
                decentCeiling.getDescription(), decentFloor.getDescription(),
                modernDevice.getDescription(), modernFurniture.getDescription()
        );


        final RenovationFactory oldFactory = new OldRenovationFactory();

        final var badFloor = oldFactory.createFloor();
        final var badCeiling = oldFactory.createCeiling();
        final var oldDevice = oldFactory.createDevice();
        final var oldFurniture = oldFactory.createFurniture();

        System.out.printf(
                "Modern renovation factory produced: %s || %s || %s || %s%n",
                badCeiling.getDescription(), badFloor.getDescription(),
                oldDevice.getDescription(), oldFurniture.getDescription()
        );
    }
}