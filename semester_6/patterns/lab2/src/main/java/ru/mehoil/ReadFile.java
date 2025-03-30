package ru.mehoil;

import java.util.Objects;

public record ReadFile(
        String filename,
        String text
) {

    public ReadFile {
        Objects.requireNonNull(filename);
        Objects.requireNonNull(text);
    }
}
