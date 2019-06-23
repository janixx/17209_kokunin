package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseListener;

public class ViewController {
    private Board board;
    private View view;
    
    private MouseListener boardListener;
    private ActionListener startButtonListener;
    private ActionListener loadButtonListener;
    private ActionListener quitButtonListener;
    private ActionListener computerButtonListener;
    private ActionListener humanButtonListener;
//    private ActionListener ButtonListener;
    
    public ViewController(Board board) {
        boardListener = new BoardListener(board);
        startButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                view.choosePaneTop();
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
                System.exit(0);
            }
        };
        
        computerButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
        
            }
        };
        
        humanButtonListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
            
            }
        };
        view = new View(board, boardListener, startButtonListener, quitButtonListener, loadButtonListener);
    }
    
    public void init() {
        view.init();
    }
    
    /*public MouseListener getBoardListener() {
        return boardListener;
    }
    
    public ActionListener getChooseButtonListener() {
        return startButtonListener;
    }
    
    public ActionListener getLoadButtonListener() {
        return loadButtonListener;
    }
    
    public ActionListener getQuitButtonListener() {
        return quitButtonListener;
    }*/
}
