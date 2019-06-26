package ru.nsu.fit.g17209.kokunin.task2.view.widgets;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.view.ViewCell;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class BoardPane extends JPanel implements PropertyChangeListener {
    private static final Dimension size = new Dimension(420, 420);
    private static final Logger log = LogManager.getLogger();
    
    private ViewCell[][] field;
    
    public BoardPane(Board board) {
        field = new ViewCell[Board.SIZE][Board.SIZE];
        setLayout(new GridLayout(Board.SIZE,Board.SIZE));
        for (int j = 0; j < Board.SIZE; j++) {
            for (int i = 0; i < Board.SIZE; i++) {
                field[i][j] = new ViewCell(i, j);
                add(field[i][j]);
            }
        }
    
        board.addCellListeners(field);
        
        setPreferredSize(size);
        setMaximumSize(size);
    }
    
    @Override
    public synchronized void addMouseListener(MouseListener l) {
        for (int j = 0; j < Board.SIZE; j++) {
            for (int i = 0; i < Board.SIZE; i++) {
                field[i][j].addMouseListener(l);
                log.debug("Mouse listener added to ViewCell with coordinates ({},{})", i,j);
            }
        }
    }
    
    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        Board board = (Board)evt.getSource();
        int flag = board.isGameFinish();
        
        for (int y = 0; y < Board.SIZE && flag < 0; ++y) {
            for (int x = 0; x < Board.SIZE; ++x) {
                if (board.isCellLocked(x,y)) {
                    field[x][y].setEnabled(false);
                } else {
                    field[x][y].setEnabled(true);
                }
            }
        }
        log.debug("Updating of the game board...");
    }
}
