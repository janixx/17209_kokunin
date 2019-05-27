package ru.nsu.fit.g17209.kokunin.task2.model.board;

import java.awt.*;

public class Turn {
    Point origin;
    Point destination;

    public Turn(Point origin, Point destination) {
        this.origin = origin;
        this.destination = destination;
    }

    public Point getOrigin() {
        return origin;
    }

    public Point getDestination() {
        return destination;
    }
}
