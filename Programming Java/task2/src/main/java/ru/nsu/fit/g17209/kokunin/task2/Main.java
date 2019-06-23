package ru.nsu.fit.g17209.kokunin.task2;

//import ru.nsu.fit.g17209.kokunin.task2.model.Game;
import ru.nsu.fit.g17209.kokunin.task2.model.Board;
import ru.nsu.fit.g17209.kokunin.task2.view.ViewController;

public class Main {
    public static void main(String[] args) {
        Board board = new Board();
        ViewController controller = new ViewController(board);
        controller.init();
        /*javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                controller.init();
                //JFrame.setDefaultLookAndFeelDecorated(true);
                View window = new View(game);
            }
        });*/
    }
}
