package ru.mehoil;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

public class Main {
    public static void main(final String[] args) {
        final var filenames = readFromCommandLine();
        System.err.println("Processing files...");

        final FileProcessor fp = new FileWordsMatcher();
        fp.processFiles(filenames);

        System.err.printf("Processed files and wrote to: %s%n", filenames.getLast());
    }

    private static List<String> readFromCommandLine() {
        System.err.println("Please, input filenames to process on new line each.\n\t -> press ENTER to start processing");
        final var scanner = new Scanner(System.in);
        final var filenames = new ArrayList<String>();
        while (true) {
            final var filename = scanner.nextLine();
            if (filename.isBlank() || filename.equals("\n")) {
                break;
            }
            filenames.add(filename);
        }
        return filenames;
    }

    private static List<String> readFromRootDir(final String dirName) throws IOException {
        final var filesDir = Paths.get(dirName);

        if (!Files.exists(filesDir) || !Files.isDirectory(filesDir)) {
            throw new IllegalArgumentException("Directory 'files' not found");
        }

        try (var stream = Files.list(filesDir)) {
            return stream
                    .filter(Files::isRegularFile)
                    .map(Path::toString)
                    .collect(Collectors.toList());
        }
    }
}