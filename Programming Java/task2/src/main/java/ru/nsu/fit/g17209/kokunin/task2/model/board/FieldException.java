package ru.nsu.fit.g17209.kokunin.task2.model.board;

public class FieldException extends Exception {
    private Position p;

    public FieldException(String message, Position position) {
        super(message);
        p = position;
    }


}
