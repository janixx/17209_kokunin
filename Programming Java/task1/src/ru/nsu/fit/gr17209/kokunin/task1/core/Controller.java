package ru.nsu.fit.gr17209.kokunin.task1.core;

import ru.nsu.fit.gr17209.kokunin.task1.CSVWriter.CSVWriter;
import ru.nsu.fit.gr17209.kokunin.task1.reports.FrequencyReportGenerator;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

public class Controller {
    private WordReader reader;
    private WordStat statisrics;
    private ReportWriter writer;

    public Controller(BufferedReader reader, BufferedWriter writer){
        this.reader = new WordReader(reader);
        this.writer = new CSVWriter(writer);
    }

    public void analyzeText() throws IOException {
        WordStat statistics = new WordStat();
        String word = null;
        while((word = reader.getWord())!= null) {
            statistics.registerWord(word);
        }
        ReportGenerator report = new FrequencyReportGenerator(statistics);
        writer.writeReport(report.getReport());
    }
}
