package ru.nsu.fit.g17209.kokunin.task2.model;

import java.awt.*;

public class Board {
    public static final int SIZE = 8;

    private Cell[][] board;
    private int countWhite;
    private int countBlack;

    public Board() {
        board = new Cell[SIZE][SIZE];
        board[SIZE/2 - 1][SIZE/2 - 1].setWhite();
        board[SIZE/2][SIZE/2].setWhite();
        board[SIZE/2 - 1][SIZE/2].setBlack();
        board[SIZE/2][SIZE/2 - 1].setBlack();
        
        countBlack = 2;
        countWhite = 2;
        /*for (Cell[] row : field) {
            for (Cell cell : row) {
                cell.clear();
            }
        }*/
    }
/*    public final Cell getCell (int x, int y) {
        if (x > SIZE || y > SIZE || x < 0 || y < 0) {
            System.out.println("Class Board, method getCell: " +
                    "bad index!!" +
                    Integer.toString(x) +
                    Integer.toString(y));
            return board[0][0];
        }

        return board[x][y];
    }*/


    boolean setCell(Point p, CellFill fill) throws BoardException {
        if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
            String message = "Uncorrected coordinate!";
            throw new BoardException(message, p);
        }
    
        if (board[p.x][p.y].isThisColor(fill)) {
            return true;
        }
        
        if (board[p.x][p.y].isOtherColor(fill)) {
            if (board[p.x][p.y].isWhite()) {
                countWhite--;
            } else {
                countBlack--;
            }
        }
        
        if (board[p.x][p.y].isWhite()) {
            countBlack++;
        } else {
            countWhite++;
        }
        
        board[p.x][p.y].setColor(fill);
        return true;
    }
    
    public boolean hasCellThisColor(int x, int y, CellFill fill) throws BoardException {
        if (x > SIZE - 1 || y > SIZE - 1 || x < 0 || y < 0) {
            String message = "Uncorrected coordinate!";
            throw new BoardException(message, new Point(x, y));
        }
        return board[x][y].isThisColor(fill);
    }
    
    public boolean hasCellThisColor(Point p, CellFill fill) throws BoardException {
        return hasCellThisColor(p.x, p.y, fill);
    }
    
    public boolean hasCellOtherColor(int x, int y, CellFill fill) throws BoardException {
        if (x > SIZE - 1 || y > SIZE - 1 || x < 0 || y < 0) {
            String message = "Uncorrected coordinate!";
            throw new BoardException(message, new Point(x, y));
        }
        return board[x][y].isOtherColor(fill);
    }
    
    public boolean hasCellOtherColor(Point p, CellFill fill) throws BoardException {
        return hasCellThisColor(p.x, p.y, fill);
    }
    
    public boolean isCellWhite(Point p) throws BoardException {
        if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
            String message = "Uncorrected coordinate!";
            throw new BoardException(message, p);
        }
        return board[p.x][p.y].isWhite();
    }
    
    public boolean isCellBlack(Point p) throws BoardException {
        if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
            String message = "Uncorrected coordinate!";
            throw new BoardException(message, p);
        }
        return board[p.x][p.y].isBlack();
    }
    
    public boolean isCellEmpty(Point p) throws BoardException {
        if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
            String message = "Uncorrected coordinate!";
            throw new BoardException(message, p);
        }
        return board[p.x][p.y].isBlack();
    }
    
    public void clear() {
        for (Cell[] row : board) {
            for (Cell cell : row) {
                cell.clear();
            }
        }
        board[SIZE/2 - 1][SIZE/2 - 1].setWhite();
        board[SIZE/2][SIZE/2].setWhite();
        board[SIZE/2 - 1][SIZE/2].setBlack();
        board[SIZE/2][SIZE/2 - 1].setBlack();
    
        countBlack = 2;
        countWhite = 2;
    }

    public int getCountWhite() {
        return countWhite;
    }

    public int getCountBlack() {
        return countBlack;
    }
}
