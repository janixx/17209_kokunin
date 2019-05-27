package ru.nsu.fit.g17209.kokunin.task2.model.board;

public class Cell {
    private CellFill content;

    public Cell() {
        content = CellFill.EMPTY;
    }

    public boolean reverseChip() {
        if (content == CellFill.EMPTY) {
            return false;
        }
        content = (content == CellFill.WHITE ? CellFill.BLACK : CellFill.WHITE);
        return true;
    }

    public void setWhite() {
        content = CellFill.WHITE;
    }

    public void setBlack() {
        content = CellFill.BLACK;
    }

    public void clear() {
        content = CellFill.EMPTY;
    }

    public CellFill getColor() {
        return content;
    }
}
