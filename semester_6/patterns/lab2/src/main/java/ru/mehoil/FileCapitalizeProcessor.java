package ru.mehoil;

public class FileCapitalizeProcessor extends FileProcessor {

    @Override
    String apply(final String fileText) {
        return fileText.toUpperCase();
    }

}
