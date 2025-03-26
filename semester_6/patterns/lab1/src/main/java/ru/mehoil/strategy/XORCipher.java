package ru.mehoil.strategy;

public class XORCipher implements CipherStrategy {

    private final int key;

    public XORCipher(final int key) {
        this.key = key;
    }

    @Override
    public String encrypt(final String str) {
        final var sb = new StringBuilder();
        for (final char c : str.toCharArray()) {
            sb.append((char) (c ^ key));
        }
        return sb.toString();
    }

    @Override
    public String decrypt(final String str) {
        return encrypt(str);
    }
}
