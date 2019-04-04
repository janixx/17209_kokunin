package ru.nsu.fit.gr17209.kokunin.task1.core;

import java.io.BufferedWriter;
import java.io.IOException;

public interface ReportWriter {
    void writeReport(BufferedWriter writer)throws IOException;
}
