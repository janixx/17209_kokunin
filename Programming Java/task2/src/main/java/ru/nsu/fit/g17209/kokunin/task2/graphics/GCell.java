package ru.nsu.fit.g17209.kokunin.task2.graphics;

import javax.swing.*;
import java.awt.*;

public class GCell extends JButton {
    public final static Color  BLACK = new Color(68, 51, 40),
                                WHITE = new Color(243,245, 197),
                                GREEN = new Color(10, 145, 4);

    private final GCellColor color;
    //private GCellState

    public GCell(GCellColor color) {
        this.color = color;
        if (color == GCellColor.BLACK) setBackground(BLACK);
        else if (color == GCellColor.WHITE) setBackground(WHITE);
        else if (color == GCellColor.GREEN) setBackground(GREEN);

        setBorder(BorderFactory.createLineBorder(BLACK));
        setVisible(true);
    }

}
