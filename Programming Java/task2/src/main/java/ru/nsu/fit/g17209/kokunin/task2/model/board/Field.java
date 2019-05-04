package ru.nsu.fit.g17209.kokunin.task2.model.board;

public class Field {
    private static final int SIZE = 8;

    private Cell[][] field;
    private int countWhite;
    private int countBlack;
    private int count;

    public Field() {
        field = new Cell[SIZE][SIZE];
        /*for (Cell[] row : field) {
            for (Cell cell : row) {
                cell.clear();
            }
        }*/
    }

    public void setCell(Position pos, CellContent fill) {

    }

    public void clear () {
        for (Cell[] row : field) {
            for (Cell cell : row) {
                cell.clear();
            }
        }
    }

    public final Cell[][] getField() {
        return field;
    }

    public int getCountWhite() {
        return countWhite;
    }

    public int getCountBlack() {
        return countBlack;
    }

    public int getCount() {
        return count;
    }
}
