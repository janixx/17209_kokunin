package ru.nsu.fit.gr17209.kokunin.task1.CSVWriter;

import ru.nsu.fit.gr17209.kokunin.task1.core.ReportRow;
import ru.nsu.fit.gr17209.kokunin.task1.core.ReportWriter;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.List;

public class CSVWriter implements ReportWriter {
    private List<ReportRow> list;

    CSVWriter(List<ReportRow> list) {
        this.list = list;
    }

    @Override
    public void writeReport(BufferedWriter writer) throws IOException {

    }
}
