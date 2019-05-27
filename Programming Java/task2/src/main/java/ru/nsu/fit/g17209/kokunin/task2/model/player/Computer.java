package ru.nsu.fit.g17209.kokunin.task2.model.player;

import ru.nsu.fit.g17209.kokunin.task2.model.board.Cell;
import ru.nsu.fit.g17209.kokunin.task2.model.board.CellFill;
import ru.nsu.fit.g17209.kokunin.task2.model.board.Field;

import java.awt.*;

public class Computer implements Player {
    Color color;

    public Computer(Color c) {
        color = c;
    }

    @Override
    public Point decision(final Field table) {
        final Cell[][] field = table.getField();
        boolean flag = false;
        int maxScore = 0;
        Point origin = new Point(0,0),
                destination = new Point(0,0);
        for (int x = 1; x < Field.SIZE; ++x) {
            for (int y = 1; y < Field.SIZE; ++y) {
                if (table.getField()[x][y].getColor() != CellFill.EMPTY)
                flag = isMyColor(table.getField()[x][y].getColor());
            }
        }
        return destination;
    }

    private boolean isMyColor(final CellFill cellFill) {
        return ((color == Color.BLACK) ? (cellFill == CellFill.BLACK):(cellFill == CellFill.WHITE));
    }
}
