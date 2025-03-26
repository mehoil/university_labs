package ru.mehoil.strategy;

public class CaesarCipher implements CipherStrategy {

    private static final int SHIFT = 3;

    @Override
    public String encrypt(final String str) {
        final var sb = new StringBuilder();
        for (final char c : str.toCharArray()) {
            sb.append((char) (c + SHIFT));
        }
        return sb.toString();
    }

    @Override
    public String decrypt(final String str) {
        final var sb = new StringBuilder();
        for (final char c : str.toCharArray()) {
            sb.append((char) (c - SHIFT));
        }
        return sb.toString();
    }
}
