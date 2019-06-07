package ru.nsu.fit.g17209.kokunin.task2.model;

import java.awt.*;
import java.util.ArrayList;
import java.util.Arrays;

public class Board {
    public enum Direction { UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT }
    public static final int SIZE = 8;
    
    private Cell[][] board;
    private BoardController controller;
    private int countWhite;
    private int countBlack;
    
    public Board() {
        board = new Cell[SIZE][SIZE];
        board[SIZE/2 - 1][SIZE/2 - 1].setWhite();
        board[SIZE/2][SIZE/2].setWhite();
        board[SIZE/2 - 1][SIZE/2].setBlack();
        board[SIZE/2][SIZE/2 - 1].setBlack();
        
        controller = new BoardController();
        
        countBlack = 2;
        countWhite = 2;
        /*for (Cell[] row : field) {
            for (Cell cell : row) {
                cell.clear();
            }
        }*/
    }
    
    class BoardController {
        boolean valid;
        ArrayList<Point> availableWhite;
        ArrayList<Point> availableBlack;
        
        private BoardController() {
            availableWhite = new ArrayList<>(Arrays.asList(
                    new Point(Board.SIZE/2,Board.SIZE/2 - 2),
                    new Point(Board.SIZE/2 + 1,Board.SIZE/2 - 1),
                    new Point(Board.SIZE/2, Board.SIZE/2 + 1),
                    new Point(Board.SIZE/2 - 2, Board.SIZE/2)));
            availableBlack = new ArrayList<>(Arrays.asList(
                    new Point(Board.SIZE/2 - 1,Board.SIZE/2 - 2),
                    new Point(Board.SIZE/2 + 1,Board.SIZE/2),
                    new Point(Board.SIZE/2, Board.SIZE/2 + 1),
                    new Point(Board.SIZE/2 - 2, Board.SIZE/2 - 1)));
            valid = true;
        }
    
        private void setCell(Point p, Color fill) throws IllegalArgumentException {
            if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
                String message = "Uncorrected coordinate:" + p.x + p.y;
                throw new IllegalArgumentException(message);
            }
            
            valid = false;
            
            if (board[p.x][p.y].isThisColor(fill)) {
                return;
            }
        
            if (board[p.x][p.y].isAnotherColor(fill)) {
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
        }
    
        /**
         * This function watch neighbours of
         * Cell that is located in point p of
         * the board.
         * If any of eight neighbours Cells
         * has different color, function
         * retains the direction between
         * it and the source-Cell.
         */
        private ArrayList<Direction> calculateNeighbours(Point p, Color color) {
            ArrayList<Direction> directions = new ArrayList<>(0);
            if (( p.y > 0 ) && isAnotherColor(p.x, p.y - 1, color)) {
                directions.add(Direction.UP);
            }
            if (( p.x < Board.SIZE - 1 && p.y > 0 ) && isAnotherColor(p.x + 1, p.y - 1, color)) {
                directions.add(Direction.UPRIGHT);
            }
            if (( p.x < Board.SIZE - 1 ) && isAnotherColor(p.x + 1, p.y, color)) {
                directions.add(Direction.RIGHT);
            }
            if (( p.x < Board.SIZE - 1 && p.y < Board.SIZE - 1 ) && isAnotherColor(p.x + 1, p.y + 1, color)) {
                directions.add(Direction.DOWNRIGHT);
            }
            if (( p.y < Board.SIZE - 1 ) && isAnotherColor(p.x, p.y + 1, color)) {
                directions.add(Direction.DOWN);
            }
            if (( p.x > 0 && p.y < Board.SIZE - 1 ) && isAnotherColor(p.x - 1, p.y + 1, color)) {
                directions.add(Direction.DOWNLEFT);
            }
            if (( p.x > 0 ) && isAnotherColor(p.x - 1, p.y, color)) {
                directions.add(Direction.LEFT);
            }
            if (( p.x > 0 && p.y > 0 ) && isAnotherColor(p.x - 1, p.y - 1, color)) {
                directions.add(Direction.UPLEFT);
            }
            return directions;
        }
    
        /**
         * This function CHANGE the location of
         * the point that we put in arguments.
         * Returns false if Cell is empty or
         * locate outside the board.
         */
        private boolean movePointToDirection(Point p, Direction d) {
            if (p.x <= 0 || p.y <= 0 || p.x >= Board.SIZE - 1 || p.y >= Board.SIZE - 1) {
                return false;
            }
            switch (d) {
                case UP:
                    p.move(p.x, p.y - 1);
                    break;
                case UPRIGHT:
                    p.move(p.x + 1, p.y - 1);
                    break;
                case RIGHT:
                    p.move(p.x + 1, p.y);
                    break;
                case DOWNRIGHT:
                    p.move(p.x + 1, p.y + 1);
                    break;
                case DOWN:
                    p.move(p.x, p.y + 1);
                    break;
                case DOWNLEFT:
                    p.move(p.x - 1, p.y + 1);
                    break;
                case LEFT:
                    p.move(p.x - 1, p.y);
                    break;
                case UPLEFT:
                    p.move(p.x - 1, p.y - 1);
                    break;
            }
            return ( !isCellEmpty(p) );
        }
    
        private boolean checkDirection(Point p, Direction d, Color playerColor) {
            int startX = p.x, startY = p.y;
            boolean directionIsRelevant = false;
        
            /* first shift to neighbour cell; it's have another cell */
            movePointToDirection(p, d);
            while (movePointToDirection(p, d)) {
                if (isAnotherColor(p, playerColor)) {
                    directionIsRelevant = true;
                    break;
                }
            }
            p.setLocation(startX, startY);
            return directionIsRelevant;
        }
    
        private boolean checkAllDirections(Point p, ArrayList<Direction> directions, Color playerColor) {
            for (Direction direction : directions) {
                if (checkDirection(p, direction, playerColor)) {
                    return true;
                }
            }
            return false;
        }
    
        private void calculateAvailableMovies() {
            ArrayList<Point> emptyCells = new ArrayList<>(0);
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (board[i][j].isEmpty()) {
                        emptyCells.add(new Point(i, j));
                    }
                }
            }
    
            availableBlack.clear();
            availableWhite.clear();
            
            for (Point cell : emptyCells) {
                ArrayList<Direction> availableDirWhite = calculateNeighbours(cell, Color.WHITE),
                        availableDirBlack = calculateNeighbours(cell, Color.BLACK);
                if (availableDirWhite.isEmpty() && availableDirBlack.isEmpty()) continue;
        
                if (checkAllDirections(cell, availableDirWhite, Color.WHITE)) {
                    availableWhite.add(cell);
                }
                if (checkAllDirections(cell, availableDirWhite, Color.BLACK)) {
                    availableBlack.add(cell);
                }
            }
            
            valid = true;
        }
    
        private void treatMove(Point p, Color playerColor) {
            int startX = p.x, startY = p.y;
            /* array that contains number of neighbours cells with other color */
            ArrayList<Direction> directions = calculateNeighbours(p, playerColor);
            if (directions.isEmpty()) {
                System.out.println("TREAT TURN: ARRAY LIST IS EMPTY!!!");
            }
            for (Direction direction : directions) {
                if (!checkDirection(p, direction, playerColor)) {
                    directions.remove(direction);
                }
            }
            for (Direction direction : directions) {
                while (movePointToDirection(p, direction)) {
                    setCell(p, playerColor);
                }
            }
        }
    }
    
    public ArrayList<Point> getAvailableMovies(Color color) {
        if (!controller.valid) {
            controller.calculateAvailableMovies();
        }
        
        if (color == Color.WHITE) {
            return controller.availableWhite;
        } else {
            return controller.availableBlack;
        }
    }
    
    public void move(Point p, Color color) {
        ArrayList<Point> available = getAvailableMovies(color);
        if (!available.contains(p)) {
            String message = "Point " + p.x + p.y + " is not available for " + color + " player!";
            throw new IllegalArgumentException(message);
        }
        controller.treatMove(p, color);
    }
    
    public boolean isThisColor(int x, int y, Color fill) throws IllegalArgumentException {
        if (x > SIZE - 1 || y > SIZE - 1 || x < 0 || y < 0) {
            String message = "Uncorrected coordinate:" + x + y;
            throw new IllegalArgumentException(message);
        }
        return board[x][y].isThisColor(fill);
    }
    
    public boolean isThisColor(Point p, Color fill) throws IllegalArgumentException {
        return isThisColor(p.x, p.y, fill);
    }
    
    public boolean isAnotherColor(int x, int y, Color fill) throws IllegalArgumentException {
        if (x > SIZE - 1 || y > SIZE - 1 || x < 0 || y < 0) {
            String message = "Uncorrected coordinate:" + x + y;
            throw new IllegalArgumentException(message);
        }
        return board[x][y].isAnotherColor(fill);
    }
    
    public boolean isAnotherColor(Point p, Color fill) throws IllegalArgumentException {
        return isAnotherColor(p.x, p.y, fill);
    }
    
    public boolean isCellWhite(Point p) throws IllegalArgumentException {
        if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
            String message = "Uncorrected coordinate:" + p.x + p.y;
            throw new IllegalArgumentException(message);
        }
        return board[p.x][p.y].isWhite();
    }
    
    public boolean isCellBlack(Point p) throws IllegalArgumentException {
        if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
            String message = "Uncorrected coordinate:" + p.x + p.y;
            throw new IllegalArgumentException(message);
        }
        return board[p.x][p.y].isBlack();
    }
    
    public boolean isCellEmpty(Point p) throws IllegalArgumentException {
        if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
            String message = "Uncorrected coordinate:" + p.x + p.y;
            throw new IllegalArgumentException(message);
        }
        return board[p.x][p.y].isBlack();
    }
    
    void clear() {
        for (Cell[] row : board) {
            for (Cell cell : row) {
                cell.clear();
            }
        }
        board[SIZE/2 - 1][SIZE/2 - 1].setWhite();
        board[SIZE/2][SIZE/2].setWhite();
        board[SIZE/2 - 1][SIZE/2].setBlack();
        board[SIZE/2][SIZE/2 - 1].setBlack();
        
        controller = new BoardController();
    
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