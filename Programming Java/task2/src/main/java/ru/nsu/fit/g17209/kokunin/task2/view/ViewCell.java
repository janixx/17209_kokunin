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
        empty = true;
        
        setBackground(GREEN);
        setBorder(BorderFactory.createLineBorder(BLACK));
        setVisible(true);
    }
    
    public boolean isEmpty() {
        return empty;
    }
    
    public void setColor(ru.nsu.fit.g17209.kokunin.task2.model.Color color) {
        if (color == ru.nsu.fit.g17209.kokunin.task2.model.Color.BLACK) {
            setBlack();
        } else {
            setWhite();
        }
    }
    
    void setBlack() {
        empty = false;
        setDisabledIcon(black);
        setIcon(black);
        repaint();
    }
    
    void setWhite() {
        empty = false;
        setDisabledIcon(white);
        setIcon(white);
        repaint();
    }
    
    void clear() {
        empty = true;
        setIcon(null);
        setDisabledIcon(null);
        repaint();
    }
    
    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        Cell cell = (Cell)evt.getSource();
    
        if (cell.isBlack()) {
            setBlack();
        } else if (cell.isWhite()) {
            setWhite();
        }
        
        if (cell.isLocked()) {
            setEnabled(false);
        } else {
            setEnabled(true);
        }
    }
}
