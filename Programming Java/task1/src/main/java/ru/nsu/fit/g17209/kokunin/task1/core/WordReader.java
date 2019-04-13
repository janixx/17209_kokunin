package ru.nsu.fit.g17209.kokunin.task1.core;

import java.io.BufferedReader;
import java.util.Scanner;
import java.util.regex.Pattern;

public class WordReader {
    private Scanner scanner;

    WordReader(BufferedReader reader) {
        //\\p{Punct}\\p{Space}
        Pattern pattern = Pattern.compile("[\\p{Punct}\\p{Space}]+");
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
