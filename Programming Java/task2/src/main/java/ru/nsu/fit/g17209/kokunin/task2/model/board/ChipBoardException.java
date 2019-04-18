package ru.nsu.fit.g17209.kokunin.task2.model.board;

public class ChipBoardException extends Exception {
    private Position p;

    public ChipBoardException(String message, Position position) {
        super(message);
        p = position;
    }


}
