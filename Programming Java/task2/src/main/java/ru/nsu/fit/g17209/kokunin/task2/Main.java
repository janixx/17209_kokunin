package ru.nsu.fit.g17209.kokunin.task2;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.fit.g17209.kokunin.task2.view.MainWindow;
import ru.nsu.fit.g17209.kokunin.task2.view.controller.VCConfigs;
import ru.nsu.fit.g17209.kokunin.task2.view.controller.ViewController;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        /*if (args.length < 2) {
            System.out.println("Too few arguments :(");
        }*/
        VCConfigs cConfigs = new VCConfigs();
        ViewController c = new ViewController(cConfigs);
        JFrame window = new MainWindow("Reversi");
    }
}
