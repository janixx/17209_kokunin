package ru.nsu.fit.g17209.kokunin.task2.graphics;

import javax.swing.*;
import java.awt.*;

public class GSetPane extends JPanel {
    public static final Dimension MIN_SIZE = new Dimension(160, 440);
    private JButton saveButton;
    private JButton loadButton;
    private JButton startGame;
    private JButton clear;

    public GSetPane() {
        super();
        setLayout(new FlowLayout());
        add(new JButton("A"));
        add(new JButton("B"));
        add(new JButton("C"));
        setMinimumSize(MIN_SIZE);
        setBackground(Color.YELLOW);
        setSize(200, 440);
        setVisible(true);
    }
}
