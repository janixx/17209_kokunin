package ru.nsu.fit.g17209.kokunin.task2.player;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import java.awt.*;
import java.io.*;
import java.util.Scanner;

public class Human implements Player{
    @Override
    public Point decision(final Board table) {
        int x = 0, y = 0;
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String line = null;
        try {
            line = reader.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        Scanner scanner = new Scanner(line);
        if(scanner.hasNextInt()){
            x = scanner.nextInt();
        }
        if(scanner.hasNextInt()){
            y = scanner.nextInt();
        }

        return new Point(x,y);
    }
}
