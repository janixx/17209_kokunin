package ru.nsu.fit.g17209.kokunin.task2.view;

import javax.swing.*;
import java.awt.*;

public class ViewCell extends JButton {
    public final static Color
            BLACK = new Color(68, 51, 40),
            WHITE = new Color(243,245, 197),
            GREEN = new Color(10, 145, 4);
    private final static ImageIcon
            white = new ImageIcon("images/white.png"),
            black = new ImageIcon("images/black.png");


    private boolean blocked;
    private boolean empty;

    public ViewCell() {
        blocked = true;
        empty = true;
        
        setBackground(GREEN);
        setBorder(BorderFactory.createLineBorder(BLACK));
        setVisible(true);
    }
    
    public boolean isBlocked() { return blocked; }
    
    void block(boolean value) {
        blocked = value;
    }
    
    public boolean isEmpty() {
        return empty;
    }
    
    void setBlack() {
        empty = false;
        setIcon(black);
        repaint();
    }
    
    void setWhite() {
        empty = false;
        setIcon(white);
        repaint();
    }
    
    void clear() {
        empty = true;
        setIcon(null);
        repaint();
    }
}
