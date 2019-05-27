package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.controller.Observer;
import ru.nsu.fit.g17209.kokunin.task2.view.enumerations.GCellColor;
import ru.nsu.fit.g17209.kokunin.task2.view.enumerations.GCellState;
import ru.nsu.fit.g17209.kokunin.task2.view.enumerations.GPlayerColor;
import ru.nsu.fit.g17209.kokunin.task2.controller.Observable;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GCell extends JButton
        implements ActionListener, Observable /*, MouseListener*//*!!!!!*/ {

    public final static Color
            BLACK = new Color(68, 51, 40),
            WHITE = new Color(243,245, 197),
            GREEN = new Color(10, 145, 4);

    private Observer observer;
    private final GCellColor color;
    private GCellState state;
    private GPlayerColor player;

    public GCell(GCellColor color) {
        this.color = color;
        if (color == GCellColor.BLACK) setBackground(BLACK);
        else if (color == GCellColor.WHITE) setBackground(WHITE);
        else if (color == GCellColor.GREEN) setBackground(GREEN);

        this.state = GCellState.BLOCKED;

        setBorder(BorderFactory.createLineBorder(BLACK));
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {

    }

    @Override
    public void registerObserver(Observer o) {
        observer = o;
    }

    @Override
    public void notifyObservers(Point pos) {
        observer.notification(pos);
    }
}
