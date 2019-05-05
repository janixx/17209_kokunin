package ru.nsu.fit.g17209.kokunin.task2.graphics;

import ru.nsu.fit.g17209.kokunin.task2.graphics.enumerations.GCellColor;
import ru.nsu.fit.g17209.kokunin.task2.graphics.enumerations.GCellState;
import ru.nsu.fit.g17209.kokunin.task2.graphics.enumerations.GPlayerColor;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class GCell extends JButton
        implements ActionListener{

    public final static Color
            BLACK = new Color(68, 51, 40),
            WHITE = new Color(243,245, 197),
            GREEN = new Color(10, 145, 4);


    private final GCellColor color;
    private GCellState state;
    private GPlayerColor player;

    public GCell(GCellColor color) {
        this.color = color;
        if (color == GCellColor.BLACK) setBackground(BLACK);
        else if (color == GCellColor.WHITE) setBackground(WHITE);
        else if (color == GCellColor.GREEN) setBackground(GREEN);

        this.state = GCellState.BLOCKED;

        setBorder(BorderFactory.createLineBorder(BLACK));
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {

    }
}
