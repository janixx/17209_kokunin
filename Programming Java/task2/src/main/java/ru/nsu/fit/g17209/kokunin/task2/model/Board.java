package ru.nsu.fit.g17209.kokunin.task2.model;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.awt.*;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeSupport;
import java.util.ArrayList;

public class Board {
    private static final Logger LOG;
    public enum Direction {UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT}
    
    public static final int SIZE;
    
    static {
        SIZE = 8;
        LOG = LogManager.getLogger();
    }
    
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
            LOG.debug("Reset function successfully done");
        }
    
        private void setCell(int x, int y, Color fill)/* throws IllegalArgumentException*/ {
            //checkPoint(x, y);
            if (board[x][y].isThisColor(fill)) {
                return;
            }
            
            if (isCellEmpty(x,y)) {
                if (fill == Color.WHITE) {
                    countWhite++;
                } else {
                    countBlack++;
                }
            } else {
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
            }
            LOG.debug("Score changed; Black score is {}, White score is {}", countBlack, countWhite);
            
            board[x][y].setColor(fill);
            LOG.debug("Cell with coordinate {} {} set color {}", x, y, fill);
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
            
            LOG.debug("Watch all neighbours of cell with coordinate {} {}", p.x, p.y);
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
            LOG.debug("Check direction {} of cell with coordinates {} {}", d, p.x, p.y);
            return directionIsRelevant;
        }
    
        private boolean checkAllDirections(Point p, ArrayList<Direction> directions, Color color) {
            LOG.debug("Check directions {} of cell with coordinates {} {}", directions, p.x, p.y);
            for (int i = 0; i < directions.size(); i++) {
                if (checkDirection(p, directions.get(i), color)) {
                    return true;
                }
            }
            return false;
        }
    
        private void calculateAvlblMvs(Color color) {
            LOG.debug("Calculate available moves for {} player", color);
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
                            LOG.debug("Cell with coordinates {} {} is available for {}", p.x, p.y, color);
                        } else {
                            cell.setLocked(true);
                            LOG.debug("Cell with coordinates {} {} is NOT available for {}", p.x, p.y, color);
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
            LOG.debug("Treat move of {} player to cell with coordinates {} {}", player, p.x, p.y);
            /* array that contains number of neighbours cells with other color */
            ArrayList<Direction> directions = calculateNeighbours(p, player);
            ArrayList<Direction> available = new ArrayList<>(0);
            if (directions.isEmpty()) {
//                System.out.println("TREAT TURN: ARRAY LIST IS EMPTY!!!");
                LOG.error("Player {} can't move to cell with coordinate {} {}", player, p.x, p.y);
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
                
                LOG.info("Opponent ({}) hasn't moves",(player==Color.BLACK ? Color.WHITE : Color.BLACK));
                boolean playerHasMoves = ( player == Color.WHITE && availableWhite > 0 ) ||
                        ( player == Color.BLACK && availableBlack > 0 );
                
    
                if (!playerHasMoves) {
                    isPlaying = false;
                    LOG.info("Both players hasn't moves. The end of game.");
                }
            } else {
                LOG.debug("Move is passed to the opponent");
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
            LOG.error("Attempt to access a cell outside the board {} {}", x, y);
            String message = "Uncorrected coordinate: " + x + " " + y;
            throw new IllegalArgumentException(message);
        }
    }
    
    public void addBoardListener(PropertyChangeListener listener) {
        LOG.debug("Board listener added: {}", listener.getClass().getName());
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
    
    public void newGame() {
        LOG.info("Started new game");
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
    
    public void move(Point p) throws IllegalArgumentException {
        checkPoint(p.x, p.y);
        if (board[p.x][p.y].isLocked()) {
            LOG.error("Cell with coordinates ({},{}) isn't available for {} player", p.x, p.y, controller.player);
            String message = "Cell with coordinates " + p.x + p.y + " is not available for " + controller.player + " player!";
//            System.out.println(message);
            throw new IllegalArgumentException(message);
        }
        LOG.info("{} player move to cell with coordinates ({},{})", controller.player, p.x, p.y);
        controller.treatMove(p);
        
        if (!controller.isPlaying) {
            support.firePropertyChange("finish", false, true);
        }
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
        LOG.info("Calculating the winner of the game");
        return ( controller.countWhite <= controller.countBlack ?
                ( controller.countWhite == controller.countBlack ? 0 : 2 ) : 1 );
    }
    
    public int getScore(Color player) {
        return (player == Color.WHITE ? controller.countWhite : controller.countBlack);
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