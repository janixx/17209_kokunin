package ru.nsu.fit.gr17209.kokunin.task1.core;

import java.util.List;

public interface ReportGenerator {
    List<ReportRow> getReport(WordStat stat);
}
