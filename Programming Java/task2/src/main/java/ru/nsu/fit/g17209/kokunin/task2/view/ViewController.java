package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.model.Game;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseListener;

public class ViewController {
    private Game game;
    private View view;
    
    private MouseListener boardListener;
    private ActionListener chooseButtonListener;
    private ActionListener loadButtonListener;
    private ActionListener quitButtonListener;
    private ActionListener computerButtonListener;
    private ActionListener humanButtonListener;
//    private ActionListener ButtonListener;
    
    public ViewController(Game g) {
        boardListener = new BoardListener(g.getBoard());
        chooseButtonListener = new ActionListener() {
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
        view = new View(g.getBoard(), boardListener, chooseButtonListener, quitButtonListener, loadButtonListener);
    }
    
    public void init() {
        view.init();
    }
    
    /*public MouseListener getBoardListener() {
        return boardListener;
    }
    
    public ActionListener getChooseButtonListener() {
        return chooseButtonListener;
    }
    
    public ActionListener getLoadButtonListener() {
        return loadButtonListener;
    }
    
    public ActionListener getQuitButtonListener() {
        return quitButtonListener;
    }*/
}
