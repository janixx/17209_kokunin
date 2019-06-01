package ru.nsu.fit.g17209.kokunin.task2.model;

public class Cell {
    private boolean isEmpty;
    private CellFill content;

    public Cell() {
        isEmpty = true;
        content = CellFill.WHITE;
    }

    public boolean reverseChip() {
        if (isEmpty) {
            return false;
        }
        content = (content == CellFill.WHITE ? CellFill.BLACK : CellFill.WHITE);
        return true;
    }
    
    public void setColor(CellFill color) {
        isEmpty = false;
        content = color;
    }

    public void setWhite() {
        isEmpty = false;
        content = CellFill.WHITE;
    }

    public void setBlack() {
        isEmpty = false;
        content = CellFill.BLACK;
    }

    public void clear() {
        isEmpty = true;
    }

    public boolean isEmpty() { return isEmpty; }

    public boolean isThisColor(CellFill color) {
        return (!isEmpty ? (content == color) : false);
    }
    
    public boolean isOtherColor(CellFill color) { return (!isEmpty ? (content != color) : false); }

    public boolean isWhite() {
        return isThisColor(CellFill.WHITE);
    }

    public boolean isBlack() {
        return isThisColor(CellFill.BLACK);
    }
}
