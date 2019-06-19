package ru.nsu.fit.g17209.kokunin.task2.player;

import ru.nsu.fit.g17209.kokunin.task2.model.Color;
import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import java.awt.*;

public class Computer implements Player {

    public Computer() {}

    @Override
    public void move(final Board board, Color color) {
        boolean flag = false;
        int maxScore = 0;
        Point origin = new Point(0,0),
                destination = new Point(0,0);
        for (int x = 1; x < Board.SIZE; ++x) {
            for (int y = 1; y < Board.SIZE; ++y) {
                /*
                *
                * */
            }
        }
        return;
    }
/*
    private boolean isMyColor(final Color color) {
        return (( this.color == java.awt.Color.BLACK) ? ( color == Color.BLACK):( color == Color.WHITE));
    }*/
}
