package ru.nsu.fit.gr17209.kokunin.task1.core;

import java.util.Map;

public class ReportRow {
    private String[] data;

    public ReportRow(String... wordData) {
        data = wordData;
    }

    public String[] getData() {
        return data;
    }
}
