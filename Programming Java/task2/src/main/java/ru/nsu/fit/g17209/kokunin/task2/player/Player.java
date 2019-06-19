package ru.nsu.fit.g17209.kokunin.task2.player;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Color;

import java.awt.*;

/**
 * Player interface for Reversi (Othello) Game
 *
 * The Player must know his number.
 * In addition to the turn sequence, the number
 * determines the color of the player:
 * 1 always means WHITE,
 * 0 BLACK.
 * */

public interface Player {
    void move(final Board board, Color color);
}
