package ru.nsu.fit.g17209.kokunin.task2.view;

import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.view.BoardListener;

import java.awt.event.MouseListener;

public class ViewController {
    private Board board;
    
    private MouseListener boardListener;
    private MouseListener startButtonListener;
    private MouseListener stopButtonListener;

    public ViewController(Board b, BoardListener bl) {
        board = b;
        
        boardListener = bl;
        startButtonListener = null;
        stopButtonListener = null;
    }
    
    public MouseListener getBoardListener() {
        return boardListener;
    }
    
    public MouseListener getStartButtonListener() {
        return startButtonListener;
    }
    
    public MouseListener getStopButtonListener() {
        return stopButtonListener;
    }
}
