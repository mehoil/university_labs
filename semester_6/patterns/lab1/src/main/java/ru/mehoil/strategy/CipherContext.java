package ru.mehoil.strategy;

public class CipherContext {

    private CipherStrategy strategy;

    public void setStrategy(final CipherStrategy strategy) {
        this.strategy = strategy;
    }

    public String encrypt(final String plainText) {
        return strategy.encrypt(plainText);
    }

    public String decrypt(final String encryptedText) {
        return strategy.decrypt(encryptedText);
    }

}
