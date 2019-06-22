package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class ViewBoard extends JPanel implements PropertyChangeListener {
    private ViewCell[][] field;

    public ViewBoard(Board board) {
        super();
        field = new ViewCell[Board.SIZE][Board.SIZE];
        setLayout(new GridLayout(Board.SIZE,Board.SIZE));
        for (int j = 0; j < Board.SIZE; j++) {
            for (int i = 0; i < Board.SIZE; i++) {
                field[i][j] = new ViewCell(i, j);
                add(field[i][j]);
            }
        }
        
        board.addCellListeners(field);
        board.addBoardListener(this);
        /*ArrayList<Point> cells = board.getCells(Color.BLACK);
        for (Point p : cells) {
            field[p.x][p.y].setBlack();
        }
        cells = board.getCells(Color.WHITE);
        for (Point p : cells) {
            field[p.x][p.y].setWhite();
        }*/
        
        setSize(440, 440);

        setVisible(true);
    }
    
    @Override
    public synchronized void addMouseListener(MouseListener l) {
        for (int j = 0; j < Board.SIZE; j++) {
            for (int i = 0; i < Board.SIZE; i++) {
                field[i][j].addMouseListener(l);
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
    }
}