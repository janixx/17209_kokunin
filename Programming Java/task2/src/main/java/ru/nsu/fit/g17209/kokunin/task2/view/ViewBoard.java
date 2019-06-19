package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Color;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.nio.channels.Pipe;
import java.util.ArrayList;

public class ViewBoard extends JPanel /*mouse over*/ {
    private ViewCell[][] field;

    public ViewBoard(Board board) {
        super();
        field = new ViewCell[Board.SIZE][Board.SIZE];
        setLayout(new GridLayout(Board.SIZE,Board.SIZE));
        for (int i = 0; i < Board.SIZE; i++) {
            for (int j = 0; j < Board.SIZE; j++) {
                field[i][j] = new ViewCell();
                add(field[i][j]);
                //field[i][j].addMouseListener(boardListener);
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
    public synchronized void addMouseListener(MouseListener l) {
        for (int i = 0; i < Board.SIZE; i++) {
            for (int j = 0; j < Board.SIZE; j++) {
                field[i][j].addMouseListener(l);
            }
        }
    }
}