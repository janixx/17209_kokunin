package ru.nsu.fit.g17209.kokunin.task2.model.board;

import java.awt.*;

public class FieldException extends Exception {
    private Point p;

    FieldException(String message, Point position) {
        super(message);
        p = position;
    }
}
