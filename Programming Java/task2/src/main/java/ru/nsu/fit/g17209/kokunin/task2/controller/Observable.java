package ru.nsu.fit.g17209.kokunin.task2.controller;

import java.awt.*;

public interface Observable {
    void registerObserver(Observer o);
    void notifyObservers(Point pos);
}
