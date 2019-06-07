package ru.nsu.fit.g17209.kokunin.task2.model;

public class Cell {
    private boolean isEmpty;
    private Color content;

    public Cell() {
        isEmpty = true;
        content = Color.WHITE;
    }

    public boolean reverseChip() {
        if (isEmpty) {
            return false;
        }
        content = (content == Color.WHITE ? Color.BLACK : Color.WHITE);
        return true;
    }
    
    public void setColor(Color color) {
        isEmpty = false;
        content = color;
    }

    public void setWhite() {
        isEmpty = false;
        content = Color.WHITE;
    }

    public void setBlack() {
        isEmpty = false;
        content = Color.BLACK;
    }

    public void clear() {
        isEmpty = true;
    }

    public boolean isEmpty() { return isEmpty; }

    public boolean isThisColor(Color color) {
        return (!isEmpty ? (content == color) : false);
    }
    
    public boolean isAnotherColor(Color color) { return (!isEmpty ? (content != color) : false); }

    public boolean isWhite() {
        return isThisColor(Color.WHITE);
    }

    public boolean isBlack() {
        return isThisColor(Color.BLACK);
    }
}
