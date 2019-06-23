package ru.nsu.fit.g17209.kokunin.task2.model;

import java.awt.*;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;

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
        
        private void reset() {
            isPlaying = true;
            countWhite = 2;
            countBlack = 2;
            player = Color.BLACK;
            availableWhite = availableBlack = 4;
//            valid = true;
            board[Board.SIZE / 2 - 1][Board.SIZE / 2 - 2].setLocked(false);
            board[Board.SIZE / 2 + 1][Board.SIZE / 2].setLocked(false);
            board[Board.SIZE / 2][Board.SIZE / 2 + 1].setLocked(false);
            board[Board.SIZE / 2 - 2][Board.SIZE / 2 - 1].setLocked(false);
        }
    
        private void setCell(int x, int y, Color fill) throws IllegalArgumentException {
            checkPoint(x, y);
            if (board[x][y].isThisColor(fill)) {
                return;
            }
        
            if (board[x][y].isAnotherColor(fill)) {
                if (board[x][y].isWhite()) {
                    countWhite--;
                } else {
                    countBlack--;
                }
            }
        
            if (board[x][y].isWhite()) {
                countBlack++;
            } else {
                countWhite++;
            }
        
            board[x][y].setColor(fill);
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
            if (!isCellOnBoard(p.x, p.y)) {
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
            return ( isCellOnBoard(p.x, p.y) && !isCellEmpty(p.x, p.y) );
        }
    
        private boolean checkDirection(Point p, Direction d, Color color) {
            int startX = p.x, startY = p.y;
            boolean directionIsRelevant = false;
        
            /* first shift to neighbour cell; it's have another cell */
            movePointToDirection(p, d);
            while (movePointToDirection(p, d)) {
                if (isThisColor(p.x, p.y, color)) {
                    directionIsRelevant = true;
                    break;
                }
            }
            p.setLocation(startX, startY);
            return directionIsRelevant;
        }
    
        private boolean checkAllDirections(Point p, ArrayList<Direction> directions, Color color) {
            for (int i = 0; i < directions.size(); i++) {
                if (checkDirection(p, directions.get(i), color)) {
                    return true;
                }
            }
            return false;
        }
    
        private void calculateAvlblMvs(Color color) {
            int counter = 0;
            Cell cell;
            Point p = new Point(0, 0);
            ArrayList<Direction> available;
            
            for (int x = 0; x < SIZE; x++) {
                for (int y = 0; y < SIZE; y++) {
                    cell = board[x][y];
                    if (cell.isEmpty()) {
                        p.setLocation(x, y);
                        available = calculateNeighbours(p, color);
                        if (available.isEmpty()) {
                            cell.setLocked(true);
                            continue;
                        }
    
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
        }
        
        private void treatMove(Point p) {
            int startX = p.x, startY = p.y;
    
            /* array that contains number of neighbours cells with other color */
            ArrayList<Direction> directions = calculateNeighbours(p, player);
            ArrayList<Direction> available = new ArrayList<>(0);
            if (directions.isEmpty()) {
                System.out.println("TREAT TURN: ARRAY LIST IS EMPTY!!!");
            }
            for (int i = 0; i < directions.size(); i++) {
                if (checkDirection(p, directions.get(i), player)) {
                    available.add(directions.get(i));
                }
            }
            
            setCell(p.x, p.y, player);
            for (int i = 0; i < available.size(); i++) {
                while (movePointToDirection(p, available.get(i)) && isAnotherColor(p.x, p.y, player)) {
                    setCell(p.x, p.y, player);
                }
                p.setLocation(startX, startY);
            }
            
            Color opponent = ( player == Color.WHITE ? Color.BLACK : Color.WHITE );
            calculateAvlblMvs(opponent);
            
            boolean opponentHasMovies = ( opponent == Color.WHITE && availableWhite > 0 ) ||
                    ( opponent == Color.BLACK && availableBlack > 0 );
            if (!opponentHasMovies) {
                calculateAvlblMvs(player);
                boolean playerHasMoves = ( player == Color.WHITE && availableWhite > 0 ) ||
                        ( player == Color.BLACK && availableBlack > 0 );
                System.out.println("OPYAT' YA HODIT' BUDU????");
    
                if (!playerHasMoves) {
                    isPlaying = false;
                    System.out.println("GAME VSYO, FINISH!!!");
                }
            } else {
                System.out.println("OTDAJU HOD :(");
                player = opponent;
            }
            support.firePropertyChange("blocked", null, null);
        }
    }
    
    private boolean isCellOnBoard(int x, int y) {
        return (x >= 0 && y >= 0 && x < SIZE && y < SIZE);
    }
    
    private void checkPoint(int x, int y) throws IllegalArgumentException {
        if (!isCellOnBoard(x,y)) {
            String message = "Uncorrected coordinate: " + x + " " + y;
            throw new IllegalArgumentException(message);
        }
    }
    
    public void addBoardListener(PropertyChangeListener listener) {
        support.addPropertyChangeListener(listener);
        support.firePropertyChange(null, null, null);
    }
    
    public void addCellListeners(PropertyChangeListener[][] listeners) {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                board[i][j].addListener(listeners[i][j]);
            }
        }
    }
    
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
    
    public void newGame() {
        for (Cell[] row : board) {
            for (Cell cell : row) {
                cell.clear();
            }
        }
        
        board[SIZE / 2 - 1][SIZE / 2 - 1].setWhite();
        board[SIZE / 2][SIZE / 2].setWhite();
        board[SIZE / 2 - 1][SIZE / 2].setBlack();
        board[SIZE / 2][SIZE / 2 - 1].setBlack();
        
        controller.reset();
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
        
        return ( controller.countWhite <= controller.countBlack ?
                ( controller.countWhite == controller.countBlack ? 0 : 2 ) : 1 );
    }
    
    public boolean isThisColor(int x, int y, Color color) throws IllegalArgumentException {
        checkPoint(x, y);
        return board[x][y].isThisColor(color);
    }
    
    public boolean isAnotherColor(int x, int y, Color color) throws IllegalArgumentException {
        checkPoint(x, y);
        return board[x][y].isAnotherColor(color);
    }
    
    public boolean isCellEmpty(int x, int y) throws IllegalArgumentException {
        checkPoint(x, y);
        return board[x][y].isEmpty();
    }
    
    public boolean isCellLocked(int x, int y) throws IllegalArgumentException {
        checkPoint(x, y);
        return board[x][y].isLocked();
    }
    
    public Color getPlayerColor() {
        return controller.player;
    }
}