package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class BoardListener implements MouseListener {
    private Board model;
    //private ViewBoard view;
    
    BoardListener(Board b) {
        if (b == null) {
            throw new IllegalArgumentException("Got null link in BoardListener constructor");
        }
        model = b;
        //view = vb;
    }
    
    @Override
    public void mouseClicked(MouseEvent e) {
        ViewCell cell = (ViewCell) e.getSource();
        
        int x = e.getX() / Board.SIZE;
        int y = e.getY() / Board.SIZE;
        Point p = new Point(x, y);
        if (!model.isCellLocked(x,y)) {
            model.move(p);
        }
        //cell.repaint();
    }
    
    @Override
    public void mousePressed(MouseEvent e) {
    
    }
    
    @Override
    public void mouseReleased(MouseEvent e) {
    
    }
    
    @Override
    public void mouseEntered(MouseEvent e) {
    
    }
    
    @Override
    public void mouseExited(MouseEvent e) {
        ViewCell cell = (ViewCell) e.getSource();
        
//        cell
    }
}
