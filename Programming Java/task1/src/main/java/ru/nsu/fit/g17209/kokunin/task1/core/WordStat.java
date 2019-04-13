package ru.nsu.fit.g17209.kokunin.task1.core;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class WordStat {
    private Map<String, MutableInt> map;//вместо интеджера хранить специальные объекты которые можно изменять
    private int count;
    WordStat(){
        map = new HashMap<>();
        count = 0;
    }

    public void registerWord(String word) {
        if(map.containsKey(word)) {
            map.get(word).increment();
        }
        else {
            MutableInt value = new MutableInt(1);
            map.put(word, value);
        }
        //map.put(word, map.containsKey(word) ? map.get(word) + 1 : 1);
        count++;
    }

    public List<Map.Entry<String, MutableInt>> getData() {
        return new ArrayList<>(map.entrySet());
    }

    public int getWordCount() {
        return count;
    }

    public void clear() {
        map.clear();
        count = 0;
    }
}