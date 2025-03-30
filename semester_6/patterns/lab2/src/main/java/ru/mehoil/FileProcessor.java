package ru.mehoil;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public abstract class FileProcessor {

    private static final int MIN_FILES_COUNT = 2;
    protected static final String FILES_DELIMITER = "\n------------------------------------------------------\n";

    final void processFiles(final List<String> filenames) {
        final var readFiles = readFiles(filenames);

        final var output = processAll(readFiles);

        writeToLastFile(filenames, output);
    }

    protected abstract String processAll(final List<ReadFile> readFiles);

    private List<ReadFile> readFiles(final List<String> filenames) {
        if (filenames.size() < MIN_FILES_COUNT) {
            throw new IllegalArgumentException("Need at least %s files: input files + output file".formatted(MIN_FILES_COUNT));
        }
        final var readFiles = new ArrayList<ReadFile>();
        filenames.stream()
                .limit(filenames.size() - 1)
                .forEachOrdered(filename -> {
                    try (final var br = new BufferedReader(new FileReader(filename))) {
                        final var content = br.lines()
                                .collect(Collectors.joining("\n"));
                        readFiles.add(new ReadFile(filename, content));
                    } catch (final IOException e) {
                        throw new UncheckedIOException("Cannot read files", e);
                    }
                });
        return readFiles;
    }

    private void writeToLastFile(final List<String> filenames, final String data) {
        final var filename = filenames.getLast();
        try (final var fos = new FileOutputStream(filename)) {
            fos.write(data.getBytes());
        } catch (final IOException e) {
            throw new IllegalArgumentException("Cannot write to file (the last provided one)", e);
        }
    }

}
