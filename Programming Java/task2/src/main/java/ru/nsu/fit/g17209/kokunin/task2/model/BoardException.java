package ru.nsu.fit.g17209.kokunin.task2.model;

import java.awt.*;

public class BoardException extends Exception {
    private Point p;

    BoardException(String message, Point position) {
        super(message);
        p = position;
    }
}
