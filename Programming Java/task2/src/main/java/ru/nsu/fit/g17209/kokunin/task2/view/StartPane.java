package ru.nsu.fit.g17209.kokunin.task2.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

class StartPane extends JPanel {
    private JButton chooseButton;
    private JButton quitButton;
    private JButton loadButton;
    
    StartPane(ActionListener choose, ActionListener quit, ActionListener load) {
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
        chooseButton = new JButton();
        chooseButton.setBackground(new Color(-1052262));
        chooseButton.setText("Choose opponent");
        chooseButton.addActionListener(choose);
        GridBagConstraints gbc;
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(chooseButton, gbc);
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