package ru.nsu.fit.g17209.kokunin.task2.view;

import javax.swing.*;
import java.awt.*;

public class SetPane extends JPanel {
    public static final Dimension MIN_SIZE = new Dimension(160, 440);
    private JButton startButton;
    private JButton saveButton;
    private JButton loadButton;
    private JButton settingsButton;

//    public SetPane() {
//        super();
//        setLayout(new FlowLayout());
//        add(new JButton("A"));
//        add(new JButton("B"));
//        add(new JButton("C"));
//        setMinimumSize(MIN_SIZE);
//        setBackground(Color.YELLOW);
//        setSize(200, 440);
//        setVisible(true);
//    }

    public SetPane() {
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
        saveButton = new JButton();
        saveButton.setBackground(new Color(-1052262));
        saveButton.setText("Save");
        GridBagConstraints gbc;
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(saveButton, gbc);
        loadButton = new JButton();
        loadButton.setBackground(new Color(-1052262));
        loadButton.setText("Load");
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(loadButton, gbc);
        settingsButton = new JButton();
        settingsButton.setBackground(new Color(-1052262));
        settingsButton.setText("Settings");
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(settingsButton, gbc);
        startButton = new JButton();
        startButton.setBackground(new Color(-1052262));
        startButton.setText("Start");
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(startButton, gbc);
    }

}
