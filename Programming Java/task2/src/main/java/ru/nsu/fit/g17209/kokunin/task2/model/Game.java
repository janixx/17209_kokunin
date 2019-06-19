package ru.nsu.fit.g17209.kokunin.task2.model;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.player.Player;

public class Game {
    //private static Logger log = LogManager.getLogger();
    private boolean isPlaying = false;
    private Color curPlr;

    private Player whitePlayer;
    private Player blackPlayer;
    private Board board;

    public Game(Player p1, Player p2) {
        board = new Board();
        whitePlayer = p1;
        blackPlayer = p2;
        isPlaying = false;
    }

    public Board getBoard() { return board; }
    
    public boolean isGameOn() { return isPlaying; }

    public void startGame() {
        isPlaying = true;
        curPlr = Color.BLACK;
    }
    
    public void nextTurn() {
        if (curPlr == Color.WHITE) {
            whitePlayer.move(board, curPlr);
        } else {
            blackPlayer.move(board, curPlr);
        }
        
        boolean whiteHasMoves = !board.getAvlblMvs(Color.WHITE).isEmpty();
        boolean blackHasMoves = !board.getAvlblMvs(Color.BLACK).isEmpty();
    
        if (!blackHasMoves && !whiteHasMoves) {
            isPlaying = false;
            return;
        }
        
        curPlr = (curPlr == Color.WHITE ?
                        (blackHasMoves ? Color.BLACK : Color.WHITE)
                        : (whiteHasMoves ? Color.WHITE : Color.BLACK));
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
