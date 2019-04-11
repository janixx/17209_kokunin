package ru.nsu.fit.gr17209.kokunin.task1.csvwriter;

import ru.nsu.fit.gr17209.kokunin.task1.core.ReportRow;
import ru.nsu.fit.gr17209.kokunin.task1.core.ReportWriter;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.List;

public class CSVWriter implements ReportWriter {
    private BufferedWriter writer;

    public CSVWriter(BufferedWriter writer) {
        this.writer = writer;
    }

    @Override
    public void writeReport(List<ReportRow> reportList) throws IOException {
        for (ReportRow node : reportList) {
            StringBuilder toWrite = new StringBuilder();
            for (String elem : node.getData()) {
                toWrite.append(elem).append(", ");
            }
            toWrite.delete(toWrite.length() - 2, toWrite.length());
            writer.write(toWrite.toString(),0,toWrite.length());
            writer.newLine();
        }
    }

    private static String prepareElem(String elem) {
        if (elem.contains(",") || elem.contains("\"")) {// asb
            elem.replace("\"", "\"\"");
            elem = "\"" + elem + "\"";
        }
        return elem;
    }
}
