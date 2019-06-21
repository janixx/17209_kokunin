package ru.nsu.fit.g17209.kokunin.task2.model;

import java.awt.*;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;
import java.util.Arrays;

public class Board {
    public enum Direction {UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT}
    
    public static final int SIZE = 8;
    
    private PropertyChangeSupport support = new PropertyChangeSupport(this);
    private BoardController controller;
    private Cell[][] board;
    
    public Board() {
        board = new Cell[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = new Cell();
            }
        }
        board[SIZE / 2 - 1][SIZE / 2 - 1].setWhite();
        board[SIZE / 2][SIZE / 2].setWhite();
        board[SIZE / 2 - 1][SIZE / 2].setBlack();
        board[SIZE / 2][SIZE / 2 - 1].setBlack();
        
        controller = new BoardController();
    }
    
    class BoardController {
        private int countWhite;
        private int countBlack;
        private Color player;
        private boolean isPlaying;
        
        boolean valid;
        private int availableWhite;
        private int availableBlack;
        
        private BoardController() {
            isPlaying = true;
            countWhite = 2;
            countBlack = 2;
            player = Color.BLACK;
            availableWhite = availableBlack = 4;
            //calculateAvlblMvs(player);
            valid = true;
                    /*new ArrayList<>(Arrays.asList(
                    new Point(Board.SIZE / 2, Board.SIZE / 2 - 2),
                    new Point(Board.SIZE / 2 + 1, Board.SIZE / 2 - 1),
                    new Point(Board.SIZE / 2, Board.SIZE / 2 + 1),
                    new Point(Board.SIZE / 2 - 2, Board.SIZE / 2)));*/
//            board[Board.SIZE/2][Board.SIZE/2 - 2].setAvailableWhite(true);
//            board[Board.SIZE/2 + 1][Board.SIZE/2 - 1].setAvailableWhite(true);
//            board[Board.SIZE/2][Board.SIZE/2 + 1].setAvailableWhite(true);
//            board[Board.SIZE/2 - 2][Board.SIZE/2].setAvailableWhite(true);
            
            /*availableBlack *//*= new ArrayList<>(Arrays.asList(
                    new Point(Board.SIZE / 2 - 1, Board.SIZE / 2 - 2),
                    new Point(Board.SIZE / 2 + 1, Board.SIZE / 2),
                    new Point(Board.SIZE / 2, Board.SIZE / 2 + 1),
                    new Point(Board.SIZE / 2 - 2, Board.SIZE / 2 - 1)));*/
            board[Board.SIZE/2 - 1][Board.SIZE/2 - 2].setLocked(false);
            board[Board.SIZE/2 + 1][Board.SIZE/2].setLocked(false);
            board[Board.SIZE/2][Board.SIZE/2 + 1].setLocked(false);
            board[Board.SIZE/2 - 2][Board.SIZE/2 - 1].setLocked(false);
        }
    
        private void setCell(Point p, Color fill) throws IllegalArgumentException {
            if (p.x > SIZE - 1 || p.y > SIZE - 1 || p.x < 0 || p.y < 0) {
                String message = "Uncorrected coordinate:" + p.x + p.y;
                throw new IllegalArgumentException(message);
            }
            
            if (board[p.x][p.y].isThisColor(fill)) {
                return;
            }
        
            valid = false;
        
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
                if (isThisColor(p, playerColor)) {
                    directionIsRelevant = true;
                    break;
                }
            }
            p.setLocation(startX, startY);
            return directionIsRelevant;
        }
    
        private boolean checkAllDirections(Point p, ArrayList<Direction> directions, Color playerColor) {
            for (int i = 0; i < directions.size(); i++) {
                if (checkDirection(p, directions.get(i), playerColor)) {
                    return true;
                }
            }
            return false;
        }
    
        private void calculateAvlblMvs(Color color) {
            int counter = 0;
            Point p = new Point(0,0);
            for (int x = 0; x < SIZE; x++) {
                for (int y = 0; y < SIZE; y++) {
                    Cell cell = board[x][y];
                    if (cell.isEmpty()) {
                        p.setLocation(x,y);
                        ArrayList<Direction> available = calculateNeighbours(p, color);
                        if (available.isEmpty()) continue;
    
                        if (checkAllDirections(p, available, color)) {
                            cell.setLocked(false);
                            ++counter;
                        } else {
                            cell.setLocked(true);
                        }
                    }
                }
            }
            
            if (color == Color.BLACK) {
                availableBlack = counter;
            } else {
                availableWhite = counter;
            }
            //I can try to use operator new
//            availableBlack.clear();
//            availableWhite.clear();
            /*
            for (Point cell : emptyCells) {
                ArrayList<Direction> available = calculateNeighbours(cell, player);
                if (available.isEmpty()) continue;
    
                if (checkAllDirections(cell, available, player)) {
                    board[cell.x][cell.y].setLocked(false);
                }
            }
            */
        }
        
        private void treatMove(Point p) {
//            int startX = p.x, startY = p.y;
            /* array that contains number of neighbours cells with other color */
            ArrayList<Direction> directions = calculateNeighbours(p, player);
            ArrayList<Direction> available = new ArrayList<>(0);
            if (directions.isEmpty()) {
                System.out.println("TREAT TURN: ARRAY LIST IS EMPTY!!!");
            }
            for (int i = 0; i < directions.size(); i++) {
                if (!checkDirection(p, directions.get(i), player)) {
                    available.add(directions.get(i));
                }
            }
            for (Direction direction : available) {
                while (movePointToDirection(p, direction)) {
                    setCell(p, player);
                }
            }
            
            Color opponent = (player == Color.WHITE ? Color.BLACK : Color.WHITE);
            calculateAvlblMvs(opponent);
            
            boolean opponentHasMovies = (opponent == Color.WHITE && availableWhite <= 0) ||
                    (opponent == Color.BLACK && availableBlack <= 0);
            if (!opponentHasMovies) {
                calculateAvlblMvs(player);
                boolean playerHasMoves = (player == Color.WHITE && availableWhite <= 0) ||
                        (player == Color.BLACK && availableBlack <= 0);
                if (!playerHasMoves) {
                    isPlaying = false;
                }
            } else {
                player = opponent;
            }
            support.firePropertyChange("blocked", null, null);
        }
    }
    
    public void addBoardListener(PropertyChangeListener listener) {
        support.addPropertyChangeListener(listener);
        support.firePropertyChange(null, null, null);
    }
    
    public void addCellListeners(PropertyChangeListener[][] listeners) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j].addListener(listeners[i][j]);
                board[i][j].reverseChip();
                board[i][j].reverseChip();
            }
        }
    }
    
    /*public ArrayList<Point> getAvlblMvs(Color color) {
        if (!controller.valid) {
            controller.calculateAvlblMvs();
        }
        
        if (color == Color.WHITE) {
            return controller.availableWhite;
        } else {
            return controller.availableBlack;
        }
    }*/
    
    public void move(Point p) throws IllegalArgumentException {
        if (board[p.x][p.y].isLocked()) {
            String message = "Point " + p.x + p.y + " is not available for " + controller.player + " player!";
            System.out.println(message);
            throw new IllegalArgumentException(message);
        }
        controller.treatMove(p);
        
        if (!controller.isPlaying) {
            support.firePropertyChange("finish", false, true);
        }
    }
    
    void clear() {
        for (Cell[] row : board) {
            for (Cell cell : row) {
                cell.clear();
            }
        }
        board[SIZE / 2 - 1][SIZE / 2 - 1].setWhite();
        board[SIZE / 2][SIZE / 2].setWhite();
        board[SIZE / 2 - 1][SIZE / 2].setBlack();
        board[SIZE / 2][SIZE / 2 - 1].setBlack();
        
        controller = new BoardController();

//        countBlack = 2;
//        countWhite = 2;
    }
    
    /***
     * This function returns values:
     * -1 - game isn't finished
     * 0 - after finish a drawn game
     * 1 - after white win
     * 2 - after black win
     * */
    public int isGameFinish() {
        if (controller.isPlaying) {
            return -1;
        }
        
        return(controller.countWhite <= controller.countBlack ?
                (controller.countWhite == controller.countBlack ? 0 : 2) : 1);
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
    
    public boolean isCellLocked(int x, int y) throws IllegalArgumentException {
        if (x > SIZE - 1 || y > SIZE - 1 || x < 0 || y < 0) {
            String message = "Uncorrected coordinate:" + x + y;
            System.out.println(message);
            throw new IllegalArgumentException(message);
        }
        return board[x][y].isLocked();
    }
    
    public Color getPlayerColor() {
        return controller.player;
    }
    /*public ArrayList<Point> getCells(Color color) {
        ArrayList<Point> ret = new ArrayList<>(0);
        for (int i = 0; i < Board.SIZE; i++) {
            for (int j = 0; j < Board.SIZE; j++) {
                if(isThisColor(i, j, color)) ret.add(new Point(i, j));
            }
        }
        return ret;
    }*/
    
//    public int getCountWhite() {
//        return countWhite;
//    }
    
//    public int getCountBlack() {
//        return countBlack;
//    }
}