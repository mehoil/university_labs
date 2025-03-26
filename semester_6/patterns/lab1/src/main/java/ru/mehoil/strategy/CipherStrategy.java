package ru.mehoil.strategy;

public interface CipherStrategy {

    String encrypt(String str);
    String decrypt(String str);

}
