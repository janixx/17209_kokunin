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

    public FrequencyReportGenerator(WordStat stat) {
        this.stat = stat;
    }

    @Override
    public List<ReportRow> getReport() {
        List<Map.Entry<String, WordStat.MutableInt>> entryList = stat.getData();
        entryList.sort((o1, o2) -> {
            if (o2.getValue().equals(o1.getValue()))
                return o1.getKey().compareTo(o2.getKey());
            return o2.getValue().compareTo(o1.getValue());
        });
        List<ReportRow> list = new ArrayList<>();
        for (Map.Entry<String, WordStat.MutableInt> elem : entryList) {
            list.add(new ReportRow
                    (elem.getKey(),
                    Double.toString((double)(100 * elem.getValue().intValue()) / stat.getWordCount()) + '%',
                    elem.getValue().toString()));
        }
        return list;
    }
    public int getCount() {
        return stat.getWordCount();
    }
}
