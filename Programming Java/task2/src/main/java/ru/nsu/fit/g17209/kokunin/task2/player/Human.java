package ru.nsu.fit.g17209.kokunin.task2.player;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Color;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.*;
import java.util.Scanner;

public class Human implements Player, MouseListener {
    @Override
    public void move(final Board board, Color color) {
        int x = 0, y = 0;
        /*BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
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
        }*/
        
       // board.move(new Point(x,y), color);

        return;
    }
    
    @Override
    public void mouseClicked(MouseEvent e) {
    
    }
    
    @Override
    public void mousePressed(MouseEvent e) {
    
    }
    
    @Override
    public void mouseReleased(MouseEvent e) {
    
    }
    
    @Override
    public void mouseEntered(MouseEvent e) {
    
    }
    
    @Override
    public void mouseExited(MouseEvent e) {
    
    }
}
