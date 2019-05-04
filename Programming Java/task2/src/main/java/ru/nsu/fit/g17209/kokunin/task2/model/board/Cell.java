package ru.nsu.fit.g17209.kokunin.task2.model.board;

public class Cell {
    private CellContent content;

    public Cell() {
        content = CellContent.EMPTY;
    }

    public boolean reverseChip() {
        if (content == CellContent.EMPTY) {
            return false;
        }
        content = (content == CellContent.WHITE_CHIP ? CellContent.BLACK_CHIP : CellContent.WHITE_CHIP);
        return true;
    }

    public void setChipWhite() {
        content = CellContent.WHITE_CHIP;
    }

    public void setChipBlack() {
        content = CellContent.BLACK_CHIP;
    }

    public void clear() {
        content = CellContent.EMPTY;
    }

    public CellContent getChipColor() {
        return content;
    }
}
