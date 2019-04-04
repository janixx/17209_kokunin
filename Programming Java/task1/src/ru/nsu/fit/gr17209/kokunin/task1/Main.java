package ru.nsu.fit.gr17209.kokunin.task1;

import java.io.*;

public class Main {

    public static void main(String[] args) {
        Reader reader;
        Writer writer;
        switch (args.length) {
            case 1:
                try {
                    reader = new BufferedReader(new FileReader(args[0]));
                } catch (FileNotFoundException exc) {
                    System.err.println(exc.getMessage());
                    System.out.println("File not found. I will use System.in");
                    reader = new BufferedReader(new InputStreamReader(System.in));
                }
                writer = new BufferedWriter(new OutputStreamWriter(System.out));
                break;
            case 2:
                try {
                    reader = new BufferedReader(new FileReader(args[0]));
                    writer = new BufferedWriter(new FileWriter(args[1]));
                } catch (FileNotFoundException exc) {
                    System.err.println(exc.getMessage());
                    System.out.println("File not found. I will use System.in");
                    reader = new BufferedReader(new InputStreamReader(System.in));
                } catch (IOException exc) {
                    System.err.println(exc.getMessage());
                    System.out.println("File not found. I will use System.out");
                    writer = new BufferedWriter(new OutputStreamWriter(System.out));
                }
                break;
                default:
                    reader = new BufferedReader(new InputStreamReader(System.in));
                    writer = new BufferedWriter(new OutputStreamWriter(System.out));
                    break;
        }

        
    }
}
