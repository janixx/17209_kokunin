package ru.nsu.fit.g17209.kokunin.task2;

import ru.nsu.fit.g17209.kokunin.task2.model.Game;
import ru.nsu.fit.g17209.kokunin.task2.player.Human;
import ru.nsu.fit.g17209.kokunin.task2.player.Player;
import ru.nsu.fit.g17209.kokunin.task2.view.MainWindow;
import ru.nsu.fit.g17209.kokunin.task2.view.View;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        /*if (args.length < 2) {
            System.out.println("Too few arguments :(");
        }*/
        Player p1 = new Human(),
                p2 = new Human();
        Game game = new Game(p1, p2);
    
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                //JFrame.setDefaultLookAndFeelDecorated(true);
                View window = new View(game);
            }
        });
    }
}
