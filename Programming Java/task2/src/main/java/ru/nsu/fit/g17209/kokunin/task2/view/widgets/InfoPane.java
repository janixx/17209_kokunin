package ru.nsu.fit.g17209.kokunin.task2.view.widgets;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Color;
import ru.nsu.fit.g17209.kokunin.task2.view.ViewCell;

import javax.swing.*;
import java.awt.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

public class InfoPane extends JPanel implements PropertyChangeListener {
    private static final Dimension size = new Dimension(420, 20);
    private final JLabel whiteScore = new JLabel("WHITE score: ");
    private final JLabel blackScore = new JLabel("BLACK score: ");
    private final String white = "MOVE of WHITE",
                        black = "MOVE Of BLACK";
    private Board board;
    private JLabel player;
    private JLabel whiteCount;
    private JLabel blackCount;
    
    public InfoPane(Board board) {
        setLayout(new GridBagLayout());
        player = new JLabel();
        whiteCount = new JLabel();
        blackCount = new JLabel();
        this.board = board;
        GridBagConstraints gbc;
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = -0.1;
        gbc.fill = GridBagConstraints.VERTICAL;
        add(whiteScore, gbc);
    
        gbc.gridx = 1;
        gbc.gridy = 0;
        gbc.weightx = 0.1;
        gbc.fill = GridBagConstraints.VERTICAL;
        add(whiteCount);
    
        gbc.gridx = 2;
        gbc.gridy = 0;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.VERTICAL;
        add(player);
    
        gbc.gridx = 3;
        gbc.gridy = 0;
        gbc.weightx = 0.1;
        gbc.fill = GridBagConstraints.VERTICAL;
        add(blackScore);
    
        gbc.gridx = 4;
        gbc.gridy = 0;
        gbc.weightx = 0.1;
        gbc.fill = GridBagConstraints.VERTICAL;
        add(blackCount);
    }
    
    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        if(board.getPlayerColor() == Color.BLACK) {
            player.setText(black);
        } else {
            player.setText(white);
        }
        
        whiteCount.setText(Integer.toString(board.getScore(Color.WHITE)));
        blackCount.setText(Integer.toString(board.getScore(Color.BLACK)));
    }
}
