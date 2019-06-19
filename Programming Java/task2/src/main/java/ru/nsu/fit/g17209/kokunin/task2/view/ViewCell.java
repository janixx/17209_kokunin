package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Cell;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class ViewCell extends JButton implements PropertyChangeListener {
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
    
    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        Cell cell = (Cell)evt.getSource();
        if (cell.isEmpty()){
            clear();
        } else if (cell.isBlack()) {
            setBlack();
        } else {
            setWhite();
        }
    }
}
