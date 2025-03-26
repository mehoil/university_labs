package ru.mehoil;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public abstract class FileProcessor {

    final void processFiles(final List<String> filenames) {
        final var readFiles = readFiles(filenames);
        final var processedFiles = readFiles.stream()
                .map(this::apply);

        final var sb = new StringBuilder();
        processedFiles.forEach(sb::append);
        final var output = sb.toString();

        writeToLastFile(filenames, output);
    }

    abstract String apply(String fileText);

    private List<String> readFiles(final List<String> filenames) {
        final var readFiles = new ArrayList<String>();
        filenames.stream()
                .limit(filenames.size() - 1)
                .forEachOrdered(filename -> {
                    try (final var fis = new FileInputStream(filename)) {
                        readFiles.add(new String(fis.readAllBytes()));
                    } catch (IOException e) {
                        throw new IllegalArgumentException("Cannot read files: the provided filename was incorrect");
                    }
                });
        return readFiles;
    }

    private void writeToLastFile(final List<String> filenames, final String data) {
        final var filename = filenames.getLast();
        try (final var fos = new FileOutputStream(filename)) {
            fos.write(data.getBytes());
        } catch (IOException e) {
            throw new IllegalArgumentException("Cannot write to file: the last provided filename was incorrect");
        }
    }

}
