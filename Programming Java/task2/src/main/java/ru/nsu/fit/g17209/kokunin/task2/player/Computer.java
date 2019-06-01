package ru.nsu.fit.g17209.kokunin.task2.player;

import ru.nsu.fit.g17209.kokunin.task2.model.CellFill;
import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import java.awt.*;

public class Computer implements Player {
    Color color;

    public Computer(Color c) {
        color = c;
    }

    @Override
    public Point decision(final Board table) {
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
        return destination;
    }

    private boolean isMyColor(final CellFill cellFill) {
        return ((color == Color.BLACK) ? (cellFill == CellFill.BLACK):(cellFill == CellFill.WHITE));
    }
}
