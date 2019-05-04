package ru.nsu.fit.g17209.kokunin.task2.controller;

import ru.nsu.fit.g17209.kokunin.task2.graphics.MainWindow;

import javax.swing.*;
import java.awt.*;

public class Controller {
    JFrame window;

    public Controller(CConfigs conf) {
        window = new MainWindow("Reversi Game");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //window.setResizable(true);
        window.setPreferredSize(new Dimension(640, 480));

        window.setVisible(true);
    }

    public void start() {

    }
}
