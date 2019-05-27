package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.controller.Observer;
import ru.nsu.fit.g17209.kokunin.task2.view.enumerations.GCellColor;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class GBoard extends JPanel
        implements MouseListener, ActionListener /*mouse over*/ {
    private JButton[][] board;

    public GBoard(Observer o) {
        super();
        board = new GCell[8][8];
        setLayout(new GridLayout(8,8));
        /* for (int i = 0; i < 8; ++i) {
            //check the correctness of bypass
            for (int j = 0; j < 8; ++j) {
                board[i][j] = new GCell(((i + j) % 2 == 1) ? GCell.GCellColor.BLACK : GCell.GCellColor.WHITE);
                add(board[i][j], layout);
                //board[i][j] = cell;
            }
        } */
        for (JButton[] row : board) {
            for (JButton cell : row) {
                cell = new GCell(GCellColor.GREEN);
                add(cell);
            }
        }
        setSize(440, 440);

        setVisible(true);
    }

    @Override
    public void mouseClicked(MouseEvent e) {

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
