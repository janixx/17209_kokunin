package ru.nsu.fit.g17209.kokunin.task2.view.widgets;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class StartPane extends JPanel {
    private JButton startButton;
    private JButton loadButton;
    private JButton quitButton;
    
    public StartPane(ActionListener start, ActionListener load, ActionListener quit) {
        super();
        setLayout(new GridBagLayout());
        setAlignmentX(0.25f);
        setAlignmentY(0.75f);
        setAutoscrolls(false);
        setBackground(new Color(-1052262));
        setDoubleBuffered(true);
        setForeground(new Color(-12307672));
        setMaximumSize(new Dimension(120000, 360000));
        setMinimumSize(new Dimension(120, 360));
        setPreferredSize(new Dimension(160, 480));
        setVerifyInputWhenFocusTarget(true);
        putClientProperty("html.disable", Boolean.FALSE);
        setBorder(BorderFactory.createTitledBorder(BorderFactory.createLineBorder(new Color(-12307672)), null));
        startButton = new JButton();
        startButton.setBackground(new Color(-1052262));
        startButton.setText("Start new game");
        startButton.addActionListener(start);
        GridBagConstraints gbc;
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(startButton, gbc);
        loadButton = new JButton();
        loadButton.setBackground(new Color(-1052262));
        loadButton.setText("Load");
        loadButton.setEnabled(false);
        loadButton.addActionListener(load);
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(loadButton, gbc);
        quitButton = new JButton();
        quitButton.setBackground(new Color(-1052262));
        quitButton.setText("Quit");
        quitButton.addActionListener(quit);
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(quitButton, gbc);
    }
}