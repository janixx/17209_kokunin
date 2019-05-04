package ru.nsu.fit.g17209.kokunin.task2.model.player;

import ru.nsu.fit.g17209.kokunin.task2.model.board.Field;
import ru.nsu.fit.g17209.kokunin.task2.model.board.PositionPair;

public interface Player {
    public PositionPair decision(final Field table);
}
