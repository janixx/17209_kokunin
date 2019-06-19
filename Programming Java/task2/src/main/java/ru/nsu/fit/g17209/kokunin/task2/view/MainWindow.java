package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Game;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseListener;
import java.awt.event.ActionListener;

public class MainWindow extends JFrame {
    public static final Dimension MIN_SIZE = new Dimension(640,480);

    private JPanel board;
    private JPanel settingsPane;

    public MainWindow(Board b, String label) {
        super(label);
        board = new ViewBoard(b);
        addMouseListener( (MouseListener)board );
        settingsPane = new SetPane();
        setLayout(new BorderLayout());
        add(board, "Center");
        add(settingsPane, "West");
        //add(new JButton("B"), "East");
        setSize(MIN_SIZE);
        setMinimumSize(MIN_SIZE);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(true);
        setVisible(true);
    }
}
