package ru.nsu.fit.gr17209.kokunin.task1;

import ru.nsu.fit.gr17209.kokunin.task1.core.Controller;

import java.io.*;

public class Main {

    public static void main(String[] args) {
        BufferedReader reader = null;
        BufferedWriter writer = null;
        if (args.length == 1) {
            try {
                reader = new BufferedReader(new FileReader(args[0]));
            } catch (FileNotFoundException exc) {
                System.err.println(exc.getMessage());
                System.out.println("File not found. I will use System.in");
                reader = new BufferedReader(new InputStreamReader(System.in));
            }
            writer = new BufferedWriter(new OutputStreamWriter(System.out));
        } else if (args.length == 2) {
            try {
                reader = new BufferedReader(new FileReader(args[0]));
                writer = new BufferedWriter(new FileWriter(args[1], false));
            } catch (FileNotFoundException exc) {
                System.err.println(exc.getMessage());
                System.out.println("File not found. I will use System.in");
                reader = new BufferedReader(new InputStreamReader(System.in));
            } catch (IOException exc) {
                System.err.println(exc.getMessage());
                System.out.println("File not found. I will use System.out");
                writer = new BufferedWriter(new OutputStreamWriter(System.out));
            }
        } else {
            reader = new BufferedReader(new InputStreamReader(System.in));
            writer = new BufferedWriter(new OutputStreamWriter(System.out));
        }
        Controller control = new Controller(reader, writer);
        try {
            control.analyzeText();
            //writer.write("It, is, a, very \n" + "simple, example, of, CSV-Table \n");
            //writer.newLine();
            writer.flush();
        } catch (IOException exc) {
            System.err.println(exc.getMessage());
        }
        return;
    }
}
