package ru.nsu.fit.g17209.kokunin.task2.model.board;

public class PositionPair {
    private Position current;
    private Position next;

    public PositionPair(Position cur, Position next) {
        this.current = cur;
        this.next = next;
    }

    public Position getCurrent() {
        return current;
    }

    public Position getNext() {
        return next;
    }
}
