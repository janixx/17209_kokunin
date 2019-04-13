package ru.nsu.fit.g17209.kokunin.task1.core;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.List;

public interface ReportWriter {
    void writeReport(List<ReportRow> reportList) throws IOException;
}
