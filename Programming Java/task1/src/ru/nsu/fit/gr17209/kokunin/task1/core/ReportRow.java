package ru.nsu.fit.gr17209.kokunin.task1.core;

import java.util.Map;

public class ReportRow {
    private String row;

    public ReportRow(String word, Integer frequency, Integer count) {
        this.row = new String(word + "***" +
                Integer.toString(count) + "***" +
                Double.toString((frequency.doubleValue() * 100 / count.doubleValue())) + '%');
    }

    public String getRow(){
        return row;
    }
}
