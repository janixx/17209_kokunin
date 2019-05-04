package ru.nsu.fit.g17209.kokunin.task2.graphics;

import javax.swing.*;
import java.awt.*;

public class GBoard extends JPanel {
    private JButton[][] board;

    public GBoard() {
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
}
