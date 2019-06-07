package ru.nsu.fit.g17209.kokunin.task2.model;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.player.Player;

public class Game {
    private static Logger log = LogManager.getLogger();
    private boolean isPlaying = false;
    private Color currentPlayer;

    private Player whitePlayer;
    private Player blackPlayer;
    private Board board;

    public Game(Player p1, Player p2) {
        board = new Board();
        whitePlayer = p1;
        blackPlayer = p2;
        isPlaying = false;
    }

    public boolean isGameOn() { return isPlaying; }

    public void startGame() {
        isPlaying = true;
        currentPlayer = Color.BLACK;
    }
    
    public void nextTurn() {
        if (currentPlayer == Color.WHITE) {
            whitePlayer.move(board, Color.WHITE);
        } else {
            blackPlayer.move(board, Color.BLACK);
        }
        
        boolean whiteHasMoves = !board.getAvailableMovies(Color.WHITE).isEmpty();
        boolean blackHasMoves = !board.getAvailableMovies(Color.BLACK).isEmpty();
        
        currentPlayer =
                (currentPlayer == Color.WHITE ?
                        (blackHasMoves ? Color.BLACK : Color.WHITE) :
                        (whiteHasMoves ? Color.WHITE : Color.BLACK));
        
        if (currentPlayer == Color.BLACK && !blackHasMoves ||
                currentPlayer == Color.WHITE && !whiteHasMoves) {
            
            isPlaying = false;
        }
    }
    
    /**
     * Returns  -1 if game not finished
     *          0 if draw,
     *          1 if white won,
     *          2 if black won.\
     */
    public int calculateResults() {
        if (isPlaying) return -1;
        
        int whiteScore = board.getCountWhite(),
                blackScore = board.getCountBlack();
        
        return (whiteScore <= blackScore ?
                (whiteScore == blackScore ? 0 : 2)
                : 1);
    }
}
