package ru.nsu.fit.g17209.kokunin.task2.model;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.player.Player;

import java.awt.*;
import java.util.ArrayList;

public class Game {
    private static Logger log = LogManager.getLogger();
    enum Direction { UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT }
    private boolean isPlaying = false;
    private boolean isFirstPlayerTurn = true;
    //private State flag = State.NOBODY;

    /* Player1 always has white color, Player2 has black */
    private Player player1;
    private Player player2;
    private Board board;

    public Game(Player p1, Player p2) {
        board = new Board();
        player1 = p1;
        player2 = p2;
        isPlaying = false;
    }

    public boolean gameOn() { return isPlaying; }

    public void startGame() {
        isPlaying = true;
        isFirstPlayerTurn = false;
    }
    
    /**
     * This function watch neighbours
     * of Cell that is located in point p
     * of the board.
     * If any of eight neighbours Cells
     * has different color, function
     * retains the direction between
     * it and the source-Cell.
     * */
    private ArrayList<Direction> calculateNeighbours(Point p) {
        /*variable that means color of current player
        * true means WHITE, false means BLACK */
        CellFill currentColor = (isFirstPlayerTurn ? CellFill.WHITE : CellFill.BLACK );
        ArrayList<Direction> directions = new ArrayList<>(0);
        try {
            if (( p.y > 0 ) && board.hasCellOtherColor(p.x, p.y - 1, currentColor)) {
                directions.add(Direction.UP);
            }
            if (( p.x < Board.SIZE - 1 && p.y > 0 ) && board.hasCellOtherColor(p.x + 1, p.y - 1, currentColor)) {
                directions.add(Direction.UPRIGHT);
            }
            if (( p.x < Board.SIZE - 1 ) && board.hasCellOtherColor(p.x + 1, p.y, currentColor)) {
                directions.add(Direction.RIGHT);
            }
            if (( p.x < Board.SIZE - 1 && p.y < Board.SIZE - 1 ) && board.hasCellOtherColor(p.x + 1, p.y + 1, currentColor)) {
                directions.add(Direction.DOWNRIGHT);
            }
            if (( p.y < Board.SIZE - 1 ) && board.hasCellOtherColor(p.x, p.y + 1, currentColor)) {
                directions.add(Direction.DOWN);
            }
            if (( p.x > 0 && p.y < Board.SIZE - 1 ) && board.hasCellOtherColor(p.x - 1, p.y + 1, currentColor)) {
                directions.add(Direction.DOWNLEFT);
            }
            if (( p.x > 0 ) && board.hasCellOtherColor(p.x - 1, p.y, currentColor)) {
                directions.add(Direction.LEFT);
            }
            if (( p.x > 0 && p.y > 0 ) && board.hasCellOtherColor(p.x - 1, p.y - 1, currentColor)) {
                directions.add(Direction.UPLEFT);
            }
        }
        catch (BoardException exc) {
            exc.getMessage();
            exc.printStackTrace();
            System.out.println("Exception is calculateNeighbours() function");
        }

        return directions;
    }

    /**
     * This function CHANGE the location of
     * the point that we put in arguments.
     * Returns false if Cell is empty or
     * locate outside the board.
     * */
    private boolean movePointToDirection(Point p, Direction d) throws BoardException {
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
            p.move(p.x - 1, p.y );
            break;
        case UPLEFT:
            p.move(p.x - 1, p.y - 1);
            break;
        }
        return (!board.isCellEmpty(p));
    }

    private void checkDirection(Point p, Direction d) {
        int startX = p.x, startY = p.y;
        CellFill currentColor = (isFirstPlayerTurn ? CellFill.WHITE : CellFill.BLACK );
        
        int counter = 0;
        boolean directionIsRelevant = false;
        try {
            while (movePointToDirection(p, d)) {
                if (board.hasCellThisColor(p, currentColor)) {
                    directionIsRelevant = true;
                    break;
                }
                counter++;
            }
    
            p.setLocation(startX, startY);
            for (int i = 0; i < counter && directionIsRelevant; i++) {
                movePointToDirection(p, d);
                board.setCell(p, currentColor);
            }
        }
        catch(BoardException exc) {
            exc.getMessage();
            exc.printStackTrace();
            System.out.println("Throws exception forawhile " + d + " checking.");
        }
        p.setLocation(startX, startY);
    }

    private void treatTurn(Point p) {
        /**
         * variable, that contains number of neighbours cells with other color
         * */
        int counter = 0;
        ArrayList<Direction> directions = calculateNeighbours(p);
        if (directions.isEmpty()) {
            System.out.println("TREAT TURN: ARRAY LIST IS EMPTY!!!");
        }
        for (Direction direction : directions) {
            checkDirection(p, direction);
        }
        
    }


    private void turn() {
        Point point;
        boolean flag = false;
        if (isFirstPlayerTurn) {
            point = player1.decision(board);
        } else {
            point = player2.decision(board);
        }

        treatTurn(point);
    }

}
