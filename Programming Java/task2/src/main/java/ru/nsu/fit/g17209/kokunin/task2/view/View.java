package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.MouseListener;

class View {
    private JFrame window;
    private ViewBoard viewBoard;
    private SetPane setPane;
    private StartPane startPane;
    private ChoosePane choosePane;
    
    View(Board b, MouseListener bl, ActionListener start, ActionListener save, ActionListener load, ActionListener quit) {
        viewBoard = null;
        viewBoard = new ViewBoard(b);
        viewBoard.addMouseListener(bl);
        
        //controller = new ViewController(g.getBoard(), listener);
        setPane = new SetPane(start, load, save, quit);
        startPane = new StartPane(start, load, quit);
//        choosePane = new ChoosePane();
        
        window = new Window();
        window.setLayout(new BorderLayout());
        //window.add(viewBoard, "Center");
        //window.add(setPane, "West");
    }
    
    /*void choosePaneTop() {
        window.remove(startPane);
        window.add(choosePane, "Center");
        window.setVisible(true);
        window.repaint();
    
    }*/
    
    void playOnBoard() {
        window.remove(startPane);
        window.add(viewBoard, "Center");
        window.add(setPane, "West");
        window.setVisible(true);
        window.repaint();
    }
    
    void init() {
//        window.add(viewBoard, "Center");
//        window.add(setPane, "West");
        window.add(startPane, "Center");
        window.setVisible(true);
//        window.repaint();
    }
    
    
}
