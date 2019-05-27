package ru.nsu.fit.g17209.kokunin.task2.model.player;

import ru.nsu.fit.g17209.kokunin.task2.model.board.Field;
import ru.nsu.fit.g17209.kokunin.task2.model.board.Turn;

import java.awt.*;

public interface Player {
    Point decision(final Field table);
}
