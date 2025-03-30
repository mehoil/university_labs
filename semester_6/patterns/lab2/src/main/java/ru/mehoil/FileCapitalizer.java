package ru.mehoil;

import java.util.List;
import java.util.stream.Collectors;

public class FileCapitalizer extends FileProcessor {

    @Override
    protected String processAll(final List<ReadFile> readFiles) {
        return readFiles.stream()
                .map(rf -> rf.text().toUpperCase())
                .collect(Collectors.joining(FILES_DELIMITER));
    }

}
