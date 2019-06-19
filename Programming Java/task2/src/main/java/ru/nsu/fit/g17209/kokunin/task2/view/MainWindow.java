package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import javax.swing.*;
import java.awt.*;

public class MainWindow extends JFrame {
    public static final Dimension MIN_SIZE = new Dimension(640,480);
    
    private ViewController view;
    private JPanel board;
    private JPanel settingsPane;

    public MainWindow(Board b) {
        super();
        setLayout(new BorderLayout());
        add(board, "Center");
        add(settingsPane, "West");
        setSize(MIN_SIZE);
        setMinimumSize(MIN_SIZE);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(true);
        setVisible(true);
    }
}
