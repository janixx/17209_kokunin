package ru.nsu.fit.gr17209.kokunin.task1.core;

import java.io.BufferedReader;
import java.util.Scanner;
import java.util.regex.Pattern;

public class WordReader {
    private Scanner scanner;
    WordReader(BufferedReader reader) {
        Pattern pattern = Pattern.compile("[^а-яА-Яa-zA-Z0-9]+");
        this.scanner = new Scanner(reader).useDelimiter(pattern);
    }

    public String getWord() {
        if (scanner.hasNext()) {
            return scanner.next();
        }
        scanner.close();
        return null;
    }
}
