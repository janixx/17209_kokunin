package ru.nsu.fit.g17209.kokunin.task2.view;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

class ChoosePane extends JPanel {
    JLabel label;
    JButton computerButton;
    JButton humanButton;
    
    ChoosePane(/*ActionListener computer, ActionListener human*/) {
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
        label = new JLabel("Choose your opponent!");
        label.setBackground(new Color(-1052262));
        GridBagConstraints gbc;
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(label, gbc);
        computerButton = new JButton();
        computerButton.setBackground(new Color(-1052262));
        computerButton.setText("Computer");
        computerButton.setEnabled(false);
        //computerButton.addActionListener(computer);
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 2;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(computerButton, gbc);
        humanButton = new JButton();
        humanButton.setBackground(new Color(-1052262));
        humanButton.setText("Human");
        //humanButton.addActionListener(human);
        gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.weightx = 1.0;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        add(humanButton, gbc);
    }
}
