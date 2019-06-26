package ru.nsu.fit.g17209.kokunin.task2.view;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.view.widgets.BoardPane;
import ru.nsu.fit.g17209.kokunin.task2.view.widgets.InfoPane;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseListener;
import java.beans.PropertyChangeListener;

public class ViewBoard extends JPanel {
    private static final Dimension size = new Dimension(420, 440);
    private static final Logger log = LogManager.getLogger();
    
    private JPanel field;
    private JPanel info;
    
    public ViewBoard(Board board) {
        super();
        setLayout(new BorderLayout());
    
        info = new InfoPane(board);
        add(info, BorderLayout.NORTH);
        
        field = new BoardPane(board);
        add(field, BorderLayout.CENTER);
    
        board.addBoardListener((PropertyChangeListener)info);
        board.addBoardListener((PropertyChangeListener)field);
    
        setMinimumSize(size);
        setPreferredSize(size);
        setVisible(true);
    }
    
    @Override
    public synchronized void addMouseListener(MouseListener l) {
        field.addMouseListener(l);
    }
}