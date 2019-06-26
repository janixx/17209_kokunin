package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import javax.swing.*;
import javax.swing.plaf.metal.MetalBorders;
import java.awt.*;

public class Window extends JFrame {
    static final Dimension MIN_SIZE = new Dimension(640,480);
    
    public Window() {
        super("Reversi Game");
        setLayout(new BorderLayout());
        setSize(MIN_SIZE);
        setMinimumSize(MIN_SIZE);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setVisible(true);
    }
}
