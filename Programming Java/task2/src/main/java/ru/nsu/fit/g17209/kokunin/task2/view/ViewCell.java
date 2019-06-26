package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Cell;

import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class ViewCell extends JButton implements PropertyChangeListener {
    public final static Color
            BLACK = new Color(49, 40, 24),
            WHITE = new Color(243,245, 197),
            GREEN = new Color(21, 141, 60),
            YELLOW = new Color(0xE7FBEE37, true);
    private final static ImageIcon
            white = new ImageIcon("images/white.png"),
            black = new ImageIcon("images/black.png");
    private final static Border
            standard = BorderFactory.createLineBorder(BLACK),
            active = BorderFactory.createLineBorder(YELLOW, 2);


    private boolean empty;
    private Point coordinates;

    public ViewCell(int x, int y) {
        empty = true;
        
        coordinates = new Point(x,y);
        setBackground(GREEN);
        setBorder(standard);
        setVisible(true);
    }
    
    public boolean isEmpty() {
        return empty;
    }
    
    public Point getLocationOnBoard(){
        return coordinates;
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
    
    public void setRedRound() {
        paintImmediately(getX()/2, getY()/2, 3, 3);
        repaint();
    }

    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        Cell cell = (Cell)evt.getSource();
    
        if (cell.isBlack()) {
            setBlack();
        } else if (cell.isWhite()) {
            setWhite();
        } else {
            clear();
        }
        
        if (cell.isLocked()) {
            this.setEnabled(false);
            this.setBorder(standard);
        } else {
            this.setEnabled(true);
            this.setBorder(active);
        }
    }
}
