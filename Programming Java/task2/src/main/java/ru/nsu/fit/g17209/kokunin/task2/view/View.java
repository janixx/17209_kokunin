package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Game;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.MouseListener;

public class View {
    private Board board;
    
    private JFrame window;
    private ViewBoard viewBoard;
    private SetPane setPane;
    private StartPane startPane;
    private ChoosePane choosePane;
    
    public View(Board b, MouseListener bl, ActionListener choose, ActionListener quit, ActionListener load) {
        board = b;
        viewBoard = new ViewBoard(b);
        viewBoard.addMouseListener(bl);
        
        //controller = new ViewController(g.getBoard(), listener);
        setPane = new SetPane();
        startPane = new StartPane(choose, quit, load);
        choosePane = new ChoosePane();
        
        window = new Window();
        window.setLayout(new BorderLayout());
        //window.add(viewBoard, "Center");
        //window.add(setPane, "West");
    }
    
    void choosePaneTop() {
        window.remove(startPane);
        window.add(choosePane, "Center");
        window.setVisible(true);
        window.repaint();
    
    }
    
    void playOnBoard() {
        window.removeAll();
        window.add(viewBoard, "Center");
        window.add(setPane, "West");
        window.setVisible(true);
    
    }
    
    public void init() {
        window.add(startPane, "Center");
        window.setVisible(true);
        window.repaint();
    }
    
    
}
