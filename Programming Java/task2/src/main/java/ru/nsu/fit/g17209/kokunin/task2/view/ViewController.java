package ru.nsu.fit.g17209.kokunin.task2.view;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseListener;

public class ViewController {
    private static final Logger LOG = LogManager.getLogger();
    
    private Board board;
    private View view;
    
    private MouseListener boardListener;
    private ActionListener startButtonListener;
    private ActionListener loadButtonListener;
    private ActionListener quitButtonListener;
    private ActionListener saveButtonListener;
    
    public ViewController() {
        board = new Board();
        boardListener = new ViewBoardListener(board);
        
        startButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                LOG.info("Start button pressed");
                view.playOnBoard();
                board.newGame();
            }
        };
        saveButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            
            }
        };
    
        loadButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            
            }
        };
    
        quitButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                LOG.info("Exit button pressed");
                System.exit(0);
            }
        };
        
        
        view = new View(board, boardListener, startButtonListener, saveButtonListener, loadButtonListener, quitButtonListener);
    }
    
    public void init() {
        view.init();
    }
}
