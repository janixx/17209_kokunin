package ru.nsu.fit.g17209.kokunin.task2;

import ru.nsu.fit.g17209.kokunin.task2.controller.CConfigs;
import ru.nsu.fit.g17209.kokunin.task2.controller.Controller;

public class Main {

    public static void main(String[] args) {
        /*if (args.length < 2) {
            System.out.println("Too few arguments :(");
        }*/
        CConfigs cConfigs = new CConfigs();
        Controller c = new Controller(cConfigs);
    }
}
