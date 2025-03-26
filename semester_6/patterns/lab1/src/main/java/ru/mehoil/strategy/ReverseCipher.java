package ru.mehoil.strategy;

public class ReverseCipher implements CipherStrategy {

    @Override
    public String encrypt(final String str) {
        return new StringBuilder(str).reverse().toString();
    }

    @Override
    public String decrypt(final String str) {
        return encrypt(str);
    }
}
