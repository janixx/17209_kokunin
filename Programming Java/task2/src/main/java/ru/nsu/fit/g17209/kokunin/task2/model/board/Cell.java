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
        content = (content == CellFill.WHITE_CHIP ? CellFill.BLACK_CHIP : CellFill.WHITE_CHIP);
        return true;
    }

    public void setChipWhite() {
        content = CellFill.WHITE_CHIP;
    }

    public void setChipBlack() {
        content = CellFill.BLACK_CHIP;
    }

    public void clear() {
        content = CellFill.EMPTY;
    }

    public CellFill getChipColor() {
        return content;
    }
}
