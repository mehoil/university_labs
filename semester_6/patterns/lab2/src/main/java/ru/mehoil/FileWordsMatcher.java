package ru.mehoil;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class FileWordsMatcher extends FileProcessor {

    @Override
    protected String processAll(final List<ReadFile> readFiles) {
        final var firstFileWords = Arrays.stream(readFiles.getFirst()
                .text().split("\\s+")
        ).collect(Collectors.toSet());

        return readFiles.stream()
                .skip(1)
                .filter(rf -> Arrays.stream(rf.text().split("\\s+"))
                        .anyMatch(firstFileWords::contains)
                )
                .map(ReadFile::filename)
                .collect(Collectors.joining(FILES_DELIMITER));
    }


}
