package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Game;

import javax.swing.*;
import java.awt.*;

public class View {
    private ViewController controller;
    private JFrame mainWindow;
    private ViewBoard board;
    private SetPane setPane;
    private Game game;
    
    public View(Game g) {
        setPane = new SetPane();
        
        board = new ViewBoard(g.getBoard());
        
        BoardListener listener = new BoardListener(g.getBoard(), board);
        board.addMouseListener(listener);
        
        controller = new ViewController(g.getBoard(), listener);
        
        mainWindow = new MainWindow(g.getBoard());
        mainWindow.setLayout(new BorderLayout());
        mainWindow.add(board, "Center");
        mainWindow.add(setPane, "West");
    }
}
