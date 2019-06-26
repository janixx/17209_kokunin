package ru.nsu.fit.g17209.kokunin.task2.view;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class ViewBoardListener implements MouseListener {
    private static final Logger LOG = LogManager.getLogger();
    private Board model;
    //private ViewBoard view;
    
    ViewBoardListener(Board b) {
        if (b == null) {
            String message = "Failed to retrieve link on Board in ViewBoardListener constructor";
            LOG.error(message);
            throw new IllegalArgumentException(message);
        }
        model = b;
        //view = vb;
    }
    
    @Override
    public void mouseClicked(MouseEvent e) {
        ViewCell cell = (ViewCell) e.getSource();
        Point p = cell.getLocationOnBoard();
        LOG.debug("Mouse clicked on cell with coordinates ({},{})", p.x, p.y);
        if (!model.isCellLocked(p.x,p.y)) {
            model.move(p);
        }
    }
    
    @Override
    public void mousePressed(MouseEvent e) {
    
    }
    
    @Override
    public void mouseReleased(MouseEvent e) {
    
    }
    
    @Override
    public void mouseEntered(MouseEvent e) {
        /*ViewCell cell = (ViewCell)e.getSource();
        Point p = cell.getLocationOnBoard();
        if (!model.isCellLocked(p.x, p.y)) {
            cell.setRedRound();
        }*/
    }
    
    @Override
    public void mouseExited(MouseEvent e) {
    
    }
}
