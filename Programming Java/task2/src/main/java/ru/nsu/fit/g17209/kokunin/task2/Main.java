package ru.nsu.fit.g17209.kokunin.task2;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.model.Game;
import ru.nsu.fit.g17209.kokunin.task2.player.Human;
import ru.nsu.fit.g17209.kokunin.task2.player.Player;
import ru.nsu.fit.g17209.kokunin.task2.view.MainWindow;
import ru.nsu.fit.g17209.kokunin.task2.view.controller.VCConfigs;
import ru.nsu.fit.g17209.kokunin.task2.view.controller.ViewController;

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
                JFrame window = new MainWindow(game.getBoard(),"Reversi");
            }
        });
    }
}
