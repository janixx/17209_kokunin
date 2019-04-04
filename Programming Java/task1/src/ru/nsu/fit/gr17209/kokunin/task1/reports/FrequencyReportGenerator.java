package ru.nsu.fit.gr17209.kokunin.task1.reports;

import ru.nsu.fit.gr17209.kokunin.task1.core.ReportGenerator;
import ru.nsu.fit.gr17209.kokunin.task1.core.ReportRow;
import ru.nsu.fit.gr17209.kokunin.task1.core.WordStat;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class FrequencyReportGenerator
    implements ReportGenerator {
    private WordStat stat;

    FrequencyReportGenerator(WordStat stat) {
        this.stat = stat;
    }

    @Override
    public List<ReportRow> getReport() {
        List<Map.Entry<String, Integer>> entryList = stat.getData();
        entryList.sort((o1,o2)->{
            if(o2.getKey().equals(o1.getKey())) {
                return o1.getValue().compareTo(o2.getValue());
            }
            return o2.getKey().compareTo(o1.getKey());
        });
        List<ReportRow> list = new ArrayList<>();
        for (Map.Entry<String, Integer> elem : entryList) {
            list.add(new ReportRow(elem.getKey(),elem.getValue(),stat.getWordCount()));
        }
        return list;
    }
}
