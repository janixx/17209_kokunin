package ru.nsu.fit.g17209.kokunin.task2.controller;

import ru.nsu.fit.g17209.kokunin.task2.model.Game;
import ru.nsu.fit.g17209.kokunin.task2.model.board.Cell;
import ru.nsu.fit.g17209.kokunin.task2.view.MainWindow;

import javax.swing.*;
import java.awt.*;

public class Controller {
    private Cell[][] board;
    private JFrame window;
    private Game model;

    Controller() {
        window = new MainWindow("Reversi Game");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //window.setResizable(true);
        window.setPreferredSize(new Dimension(640, 480));

        window.setVisible(true);
    }

}
