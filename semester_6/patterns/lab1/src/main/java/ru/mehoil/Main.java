package ru.mehoil;

import ru.mehoil.strategy.*;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        final var scanner = new Scanner(System.in);
        System.out.println("List of ciphers:");

        System.out.println("\t0. Exit");
        System.out.println("\t1. Caesar cipher");
        System.out.println("\t2. Reverse cipher");
        System.out.println("\t3. XOR cipher (with key)");

        final var ctx = new CipherContext();
        CipherStrategy strategy = null;

        boolean isRunning = true;
        while (isRunning) {
            System.out.println("\nSelect cipher algorithm: ");
            final int choice = scanner.nextInt();
            scanner.nextLine();

            System.out.println("Enter text: ");
            final String input = scanner.nextLine();

            switch (choice) {
                case 0 -> isRunning = false;
                case 1 -> strategy = new CaesarCipher();
                case 2 -> strategy = new ReverseCipher();
                case 3 -> {
                    System.out.println("Enter key for XOR cipher (int): ");
                    final int key = scanner.nextInt();
                    strategy = new XORCipher(key);
                }
            }

            if (isRunning) {
                ctx.setStrategy(strategy);
                final var encrypted = ctx.encrypt(input);
                final var decrypted = ctx.decrypt(encrypted);

                System.err.println("Encrypted text: " + encrypted);
                System.err.println("Decrypted text: " + decrypted);
            }
        }
    }
}