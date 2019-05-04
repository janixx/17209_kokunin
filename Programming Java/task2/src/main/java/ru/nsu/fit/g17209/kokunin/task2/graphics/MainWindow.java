package ru.nsu.fit.g17209.kokunin.task2.graphics;

import javax.swing.*;
import java.awt.*;

public class MainWindow extends JFrame {
    public static final Dimension MIN_SIZE = new Dimension(640,480);

    private JPanel board;
    private JPanel settingsPane;

    public MainWindow(String label) {
        super(label);
        board = new GBoard();
        settingsPane = new GSetPane();
        setLayout(new BorderLayout());
        add(board, "Center");
        add(settingsPane, "West");
        //add(new JButton("B"), "East");
        setSize(MIN_SIZE);
        setMinimumSize(MIN_SIZE);
        setResizable(true);
        setVisible(true);
    }
}
