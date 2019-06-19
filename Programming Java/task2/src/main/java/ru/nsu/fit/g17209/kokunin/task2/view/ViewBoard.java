package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Color;
import ru.nsu.fit.g17209.kokunin.task2.view.enumerations.GCellColor;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.nio.channels.Pipe;
import java.util.ArrayList;

public class ViewBoard extends JPanel
        implements MouseListener, ActionListener /*mouse over*/ {
    private ViewCell[][] field;

    public ViewBoard(Board board) {
        super();
        field = new ViewCell[Board.SIZE][Board.SIZE];
        setLayout(new GridLayout(Board.SIZE,Board.SIZE));
        for (int i = 0; i < Board.SIZE; i++) {
            for (int j = 0; j < Board.SIZE; j++) {
                field[i][j] = new ViewCell(GCellColor.GREEN);
                add(field[i][j]);
            }
        }
    
        ArrayList<Point> cells = board.getCells(Color.BLACK);
        for (Point p : cells) {
            field[p.x][p.y].setBlack();
        }
        cells = board.getCells(Color.WHITE);
        for (Point p : cells) {
            field[p.x][p.y].setWhite();
        }
        
        setSize(440, 440);

        setVisible(true);
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        ViewCell cell = (ViewCell) e.getSource();
        if (cell.isEmpty()) {
            cell.setWhite();
        } else {
            cell.clear();
        }
//        setVisible(false);
        cell.repaint();
        //this.repaint();
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

    }

    @Override
    public void actionPerformed(ActionEvent e) {

    }
}