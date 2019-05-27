package ru.nsu.fit.g17209.kokunin.task2;

import ru.nsu.fit.g17209.kokunin.task2.view.controller.VCConfigs;
import ru.nsu.fit.g17209.kokunin.task2.view.controller.ViewController;

public class Main {

    public static void main(String[] args) {
        /*if (args.length < 2) {
            System.out.println("Too few arguments :(");
        }*/
        VCConfigs cConfigs = new VCConfigs();
        ViewController c = new ViewController(cConfigs);
    }
}
